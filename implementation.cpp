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
    try
    {
        std::cout << message;
        std::cin >> selection;
        if (selection < 0 || selection > max || std::cin.fail())
            throw std::invalid_argument("Error: Invalid input.");

        char confirm = 'Y';
        promptChar(confirm, "You have selected " + std::to_string(selection) + " Proceed? Y|N: ");
        confirm = std::toupper(confirm);

        if (confirm != 'N' && confirm != 'Y')
            throw std::invalid_argument("Error: Invalid input.");
        if (confirm == 'N')
            selection = -1;
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        promptChoices(selection, max, message);
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
            std::cin.ignore();
            std::getline(std::cin, input);
        }
        else
        {
            std::cin >> input;
        }
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
        std::cout << "Error opening file: ";
        return;
    }
    Ids ids = {};
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
            std::cout << "\nEnter the video details:\n";
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
            _rentalHandler->rentVideo(customerId, videoId);
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
            displayMenu(_customerChoices);
            break;
        case 8:
        {
            // TODO
            // saveVideos();
            // saveCustomers();
            std::cout << "\nThank you for using the program!\n\nMembers:\n";
            for (auto const &member : _members)
                std::cout << "- " << member[0] << ": " << member[1] << "\n";
            std::cout << "\nThis program was brought to you by BMSCT\n-- Binary Marikina Shoe Company Tree --";
            break;
        }
        }
    } while (selection != 8);
};

// void Program::loadVideos() const
// {

// };

// void saveCustomers();

void Program::init()
{
    std::cout << "Welcome to the video store!\n";
    prompt();
}
