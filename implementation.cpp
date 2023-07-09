#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include <functional>
#include "data.hpp"

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

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
            std::cout << "Error: Invalid input\n\n";
            continue;
        }
        break;
    }
};

void BaseProgram::promptInt(
    int &input, std::string message, std::function<bool(int)> validator = [](int input)
                                     { return input <= 0; }) const
{
    prompter<int>(input, message, validator);
};
void BaseProgram::promptString(
    std::string &input, std::string message, std::function<bool(std::string)> validator = [](std::string input)
                                             { return input.empty(); }) const
{
    prompter<std::string>(input, message, validator);
};

void BaseProgram::promptChar(
    char &input, std::string message, std::function<bool(char)> validator = [](char input)
                                      { return input == '\0'; }) const
{
    prompter<char>(input, message, validator);
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

void Program::chooseDisplay()
{

    int displayOption = -1;
    std::cout << "1. Display all Customers\n";
    std::cout << "2. Choose a Customer to display\n";
    promptInt(displayOption, "Enter your choice: ", [this](int input)
              { return input == 1 || input == 2; });
    if (displayOption == 1)
        _customerHandler->displayCustomers();
    else
    {
        int customerId = -1;
        promptInt(customerId, "Enter customer ID: ", [this](int input)
                  { return !_customerHandler->customerExists(input); });
        _customerHandler->displayCustomerDetails(customerId);
    }
}
void Program::customerPrompt()
{
    int selection = -1;
    displayMenu(_customerChoices);
    promptInt(selection, "Enter your choice: ", [this](int input)
              { return input <= 0 || input > _customerChoices.size(); });
    switch (selection)
    {
    case 1:
    {

        std::string name = "", address = "";
        std::cout << "\nEnter the customer details:\n";
        promptString(name, "Name: ");
        promptString(address, "Address: ");
        ++_ids.customerId;
        _customerHandler->addCustomer(_ids.customerId, name, address);
        break;
    }
    case 2:
    {

        chooseDisplay();
        break;
    }
    case 3:
    {
        int id = 0;
        promptInt(id, "Enter the customer ID: ");
        _rentalHandler->displayRentedVideos(id);
        break;
    }
    case 4:
    {
        break;
    }
    }
};

void Program::displayMenu(std::map<int, std::string> &m) const
{
    std::cout << "\nPlease select an option:\n";
    for (auto const &choice : m)
        std::cout << choice.first << ". " << choice.second << "\n";
};

void Program::exitProgram()
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

    std::cout << "                                        ,,~~~~~~,,..\n";
    std::cout << "                             ...., ,'~             |\n";
    std::cout << "                             \\    V                /\n";
    std::cout << "                              \\  /                 /\n";
    std::cout << "                              ;####>     @@@@@     )\n";
    std::cout << "                              ##;,      @@@@@@@    )\n";
    std::cout << "                           .##/  ~>      @@@@@   .   .\n";
    std::cout << "                          ###''#>              '      '\n";
    std::cout << "      .:::::::.      ..###/ #>               '         '\n";
    std::cout << "     //////))))----~~ ## #}                '            '\n";
    std::cout << "   ///////))))))                          '             '\n";
    std::cout << "  ///////)))))))\\                        '              '\n";
    std::cout << " //////)))))))))))                                      '\n";
    std::cout << " |////)))))))))))))____________________________________).\n";
    std::cout << "|||||||||||||||||||||||||||||||||||||||||||||||||||||||||\n";
    std::cout << " ````````````````````````````'''''''''''''''''''''''''''\n";

    std::cout
        << "\nThank you for using the program!\n\nMembers:\n";
    for (auto const &member : _members)
        std::cout << "- " << member[0] << ": " << member[1] << "\n";
    std::cout << "\nThis program was brought to you by BMSCT\n-- Binary Marikina Shoe Company Tree --";
}

void Program::prompt()
{
    std::cout << "Welcome to the video store!\n";
    int selection = -1;
    do
    {
        displayMenu(_choices);
        promptInt(selection, "\nEnter your choice: ", [this](int input)
                  { return input <= 0 || input > _choices.size(); });
        switch (selection)
        {
        case 1:
        {
            int copyCount = 0;
            std::string title = "", genre = "", production = "";
            std::cout << "\nEnter the video details:\n\n";
            promptString(title, "Title: ");
            promptString(genre, "Genre: ", [this](std::string input)
                         { return !_videoStore->genreExists(input); });
            promptString(production, "Production: ");
            promptInt(copyCount, "Copy Count: ");
            ++_ids.videoId;
            _videoStore->addVideo(_ids.videoId, title, genre, production, copyCount);
            system(CLEAR);
            std::cout << "Success: Video added.\n";
            break;
        }
        case 2:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            promptInt(customerId, "Enter the customer ID: ");
            VideoStore::Video *video = _videoStore->getVideo(videoId);
            system(CLEAR);
            if (video == nullptr)
            {
                std::cout << "Info: Video not found.\n";
                break;
            }
            bool cusExists = _customerHandler->customerExists(customerId);
            if (!cusExists)
            {
                std::cout << "Info: Customer not found.\n";
                break;
            };
            ++_ids.rentalId;
            _rentalHandler->rentVideo(_ids.rentalId, customerId, videoId);
            video->removeCopy();
            break;
        }
        case 3:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            promptInt(customerId, "Enter the customer ID: ");
            VideoStore::Video *video = _videoStore->getVideo(videoId);
            system(CLEAR);
            if (video == nullptr)
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
            video->addCopy();
            break;
        }
        case 4:
        {
            int id = 0;
            promptInt(id, "Enter the video ID: ");
            VideoStore::Video *video = _videoStore->getVideo(id);
            if (video == nullptr)
                break;
            std::cout << "\nTitle: " << video->getTitle() << "\n";
            std::cout << "Genre: " << video->getGenre() << "\n";
            std::cout << "Production: " << video->getProduction() << "\n";
            std::cout << "Copy Count: " << video->getCopyCount() << "\n";
            break;
        }
        case 5:
        {
            _videoStore->displayVideos();
            break;
        }
        case 6:
        {
            int id = 0;
            promptInt(id, "Enter the video ID: ");
            VideoStore::Video *video = _videoStore->getVideo(id);
            if (video == nullptr)
                break;
            int count = video->getCopyCount();
            system(CLEAR);
            if (count > 0)
                std::cout << "Info: Video is available.\n";
            else
                std::cout << "Info: Video is not available.\n";
            break;
        }
        case 7:
        {
            system(CLEAR);
            customerPrompt();
            break;
        }
        case 8:
        {
            system(CLEAR);
            exitProgram();
            break;
        }
        }
    } while (selection != 8);
};

void Program::init()
{
    prompt();
}
