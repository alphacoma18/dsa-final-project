#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

// Program::Program() = default;
// Program::~Program() = default;

void Program::displayMenu() const
{
    std::cout << "Please select an option:" << std::endl;
    for (auto const &choice : choices)
        std::cout << choice.first << ". " << choice.second << std::endl;
};

void Program::promptChoices(int &selection, int max, std::string message) const
{
    try
    {
        std::cout << message;
        std::cin >> selection;
        if (selection < 0 || selection > max)
            throw std::invalid_argument("Invalid input.");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        promptChoices(selection, max, message);
    }
};

void Program::promptInt(int &input, std::string message) const
{
    try
    {
        std::cout << message;
        std::cin >> input;
        if (input < 0)
            throw std::invalid_argument("Invalid input.");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        promptInt(input, message);
    }
};

void Program::promptString(std::string &input, std::string message) const
{
    try
    {
        std::cout << message;
        std::getline(std::cin, input);
        if (input.empty())
            throw std::invalid_argument("Invalid input.");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        promptString(input, message);
    }
};

void Program::prompt() const
{
    displayMenu();
    int selection = -1;
    promptChoices(selection, choices.size(), "Enter your choice: ");
    std::string title = "", genre = "", production = "";
    int id = 0;
    do
    {
        switch (selection)
        {
        case 1:
            // std::cout << "Enter the video details:\n";
            // Program::promptString(title, "Title: ");
            // Program::promptString(genre, "Genre: ");
            // Program::promptString(production, "Production: ");
            // Program::promptInt(copyCount, "Copy Count: ");
            // Video *video = new Video(title, genre, production, copyCount);
            // _videoStore->addVideo(*video);
            break;
        case 2:
        {
            // promptInt(id, "Enter the video ID: ");
            // _videoStore->rentVideo(id);
            break;
        }
        case 3:
            // int id = 0;
            // promptInt(id, "Enter the video ID: ");
            // _videoStore->returnVideo(id);
            break;
        case 4:
            // int id = 0;
            // promptInt(id, "Enter the video ID: ");
            // Video *video = _videoStore->getVideo(id);
            // std::cout << "Title: " << video->getTitle() << "\n";
            // std::cout << "Genre: " << video->getGenre() << "\n";
            // std::cout << "Production: " << video->getProduction() << "\n";
            // std::cout << "Copy Count: " << video->getCopyCount() << "\n";
            break;
        case 5:
            // _videoStore->getVideos();
            break;
        case 6:
            // int id = 0;
            // promptInt(id, "Enter the video ID: ");
            // int count = _videoStore->getVideo(id)->getCopyCount();
            // if (count > 0)
            //     std::cout << "Video is available.\n";
            // else
            //     std::cout << "Video is not available.\n";
            break;
        case 7:
            // int choice = 0;
            // std::string name = "";
            // std::string address;
            // switch (choice)
            // {
            // case 1:
            //     std::cout << "Name: ";
            //     std::cin >> name;
            //     std::cout << "Address: ";
            //     std::cin >> address;
            //     account.addCustomer(name, address);
            //     break;
            // case 2:
            //     // TODO
            // }
            break;
        case 8:
            std::cout << "Thank you for using the program!\n";
            for (auto const &member : _members)
                std::cout
                    << "- " << member << "\n";
            break;
        }
    } while (selection != 8);
};

// void Program::loadVideos() const
// {
//     std::ifstream file(videosPath);
//     std::string line = "";
//     // _videoStore
// };

void Program::init()
{
    std::cout << "Welcome to the video store!" << std::endl;
    prompt();
}