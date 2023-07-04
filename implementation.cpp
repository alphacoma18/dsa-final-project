#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include <functional>
#include "data.hpp"

void BaseProgram::promptChoices(int &selection, int max, std::string message) const
{
    while (true)
    {
        std::cout << message;
        std::cin >> selection;
        if (selection < 0 || selection > max || std::cin.fail())
        {
            std::cout << "Error: Invalid input.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        char confirm = 'Y';
        promptChar(confirm, "\nYou have selected " + std::to_string(selection) + " Proceed? Y|N: ");
        confirm = std::toupper(confirm);
        if (confirm != 'N' && confirm != 'Y')
        {
            std::cout << "Error: Invalid input.\n";
            continue;
        }
        if (confirm == 'N')
            continue;
        break;
    }
};

template <typename T>
bool cinFailed()
{
    if (std::cin.fail())
    {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return true;
    }
    return false;
}

template <typename T>
void BaseProgram::prompter(T &input, std::string message, std::function<bool(T)> validator) const
{
    while (true)
    {
        std::cout << message;
        if constexpr (std::is_same<T, std::string>::value)
        {
            if (std::cin.peek() == '\n')
                std::cin.ignore();
            std::getline(std::cin, input);
        }
        else
            std::cin >> input;
        if (cinFailed<T>() || validator(input))
        {
            std::cout << "Error: Invalid input.\n";
            continue;
        }
        break;
    }
};

void BaseProgram::promptInt(int &input, std::string message) const
{
    prompter<int>(input, message, [](int input)
                  { return input < 0; });
};

void BaseProgram::promptString(std::string &input, std::string message) const
{
    prompter<std::string>(input, message, [](std::string input)
                          { return input.empty(); });
};

void BaseProgram::promptChar(char &input, std::string message) const
{
    prompter<char>(input, message, [](char input)
                   { return input == '\0'; });
};

Program::Program()
{
    _ifstream.open(_paths.persist);
    if (!_ifstream.is_open())
    {
        std::cout << "Error: Unable to load persist data\n";
        return;
    }
    std::string line = "";
    std::getline(_ifstream, line);
    _ids.videoId = std::stoi(line);
    std::getline(_ifstream, line);
    _ids.customerId = std::stoi(line);
    std::getline(_ifstream, line);
    _ids.rentalId = std::stoi(line);
    _ifstream.close();
};

Program::~Program()
{
    delete _videoStore;
    delete _customerHandler;
    delete _rentalHandler;
};

void Program::displayMenu(std::map<int, std::string> m) const
{
    std::cout << "\nPlease select an option:\n";
    for (auto const &choice : _choices)
        std::cout << choice.first << ". " << choice.second << "\n";
};

void Program::prompt()
{
    int selection = -1;
    do
    {
        displayMenu(_choices);
        promptChoices(selection, _choices.size(), "\nEnter your choice: ");
        switch (selection)
        {
        case 1:
        {
            int copyCount = 0;
            std::string title = "", genre = "", production = "";
            std::cout << "\nEnter the video details:\n\n";
            std::cin.ignore();
            promptString(title, "Title: ");
            promptString(genre, "Genre: ");
            promptString(production, "Production: ");
            promptInt(copyCount, "Copy Count: ");
            ++_ids.videoId;
            _videoStore->addVideo(new VideoStore::Video(_ids.videoId, title, genre, production, copyCount));
            std::cout << "Info: Video added.\n";
            break;
        }
        case 2:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            bool vidExists = _videoStore->videoExists(videoId);
            if (!vidExists)
            {
                std::cout << "Info: Video not found.\n";
                break;
            };
            promptInt(customerId, "Enter the customer ID: ");
            bool cusExists = _customerHandler->customerExists(customerId);
            if (!cusExists)
            {
                std::cout << "Info: Customer not found.\n";
                break;
            };
            _rentalHandler->rentVideo(_ids.rentalId, customerId, videoId);
            break;
        }
        case 3:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            promptInt(customerId, "Enter the customer ID: ");
            bool vidExists = _videoStore->videoExists(videoId);
            if (!vidExists)
            {
                std::cout << "Info: Video not found.\n";
                break;
            }
            bool cusExists = _customerHandler->customerExists(customerId);
            if (!cusExists)
            {
                std::cout << "Info: Customer not found.\n";
                break;
            }
            _rentalHandler->returnVideo(customerId, videoId);
            break;
        }
        case 4:
        {
            int id = 0;
            promptInt(id, "Enter the video ID: ");
            VideoStore::Video *video = _videoStore->getVideo(id);
            if (video == nullptr)
                break;
            std::cout << "Title: " << video->getTitle() << "\n";
            std::cout << "Genre: " << video->getGenre() << "\n";
            std::cout << "Production: " << video->getProduction() << "\n";
            std::cout << "Copy Count: " << video->getCopyCount() << "\n";
            break;
        }
        case 5:
            _videoStore->displayVideos();
            break;
        case 6:
        {
            int id = 0;
            promptInt(id, "Enter the video ID: ");
            VideoStore::Video *video = _videoStore->getVideo(id);
            if (video == nullptr)
                break;
            int count = video->getCopyCount();
            if (count > 0)
                std::cout << "Video is available.\n";
            else
                std::cout << "Video is not available.\n";
            break;
        }
        case 7:
        {
            int selection2 = -1;
            displayMenu(_customerChoices);
            promptChoices(selection2, _customerChoices.size(), "\nEnter your choice: ");
            // Todo: Paayos to sa sariling function
            switch (selection2)
            {
            case 1:
            {
                // Todo: Add Customer
                break;
            }
            case 2:
            {
                // Todo: Show Customer Details
                break;
            }
            case 3:
            {
                // Todo: List of Videos Rented by a Customer
                break;
            }
            }

            break;
        }
        case 8:
        {
            _ofstream.open(_paths.persist);
            if (!_ofstream.is_open())
            {
                std::cout << "Error: Unable to save persist data";
                return;
            }
            _ofstream << _ids.videoId << "\n";
            _ofstream << _ids.customerId << "\n";
            _ofstream << _ids.rentalId << "\n";
            _ofstream.close();

            _videoStore->saveVideos();
            _customerHandler->saveCustomers();
            _rentalHandler->saveRentals();
            std::cout
                << "\nThank you for using the program!\n\nMembers:\n";
            for (auto const &member : _members)
                std::cout << "- " << member[0] << ": " << member[1] << "\n";
            std::cout << "\nThis program was brought to you by BMSCT\n-- Binary Marikina Shoe Company Tree --";
            break;
        }
        }
    } while (selection != 8);
};

void Program::init()
{
    std::cout << "Welcome to the video store!\n";
    prompt();
}
