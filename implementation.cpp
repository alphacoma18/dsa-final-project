#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

Program::Program() = default;
Program::~Program() = default;

void Program::displayMenu() const
{
    std::cout << "Please select an option:" << std::endl;
    for (auto const &choice : _choices)
        std::cout << choice.first << ". " << choice.second << std::endl;
};

void BaseProgram::promptChoices(int &selection, int max, std::string message) const
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

void BaseProgram::promptInt(int &input, std::string message) const
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

void BaseProgram::promptString(std::string &input, std::string message) const
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

void Program::prompt()
{
    int selection = -1;
    do
    {
        displayMenu();
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
            Video *video = new Video(title, genre, production, copyCount);
            _videoStore->addVideo(video);
            break;
        }
        case 2:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            _videoStore->rentVideo(videoId);
            promptInt(customerId, "Enter the customer ID: ");
            Video *video = _videoStore->getVideo(videoId);
            if (video == nullptr)
            {
                std::cout << "Video not found.\n";
                break;
            }
            if (video->getCopyCount() == 0)
            {
                std::cout << "Video is not available.\n";
                break;
            }
            video->removeCopy();
            _customerManager->getCustomer(customerId)
                ->rentVideo(video->getId());
            break;
        }
        case 3:
        {
            int videoId = 0, customerId = 0;
            promptInt(videoId, "Enter the video ID: ");
            _videoStore->returnVideo(videoId);
            promptInt(customerId, "Enter the customer ID: ");
            Video *video = _videoStore->getVideo(videoId);
            if (video == nullptr)
            {
                std::cout << "Video not found.\n";
                break;
            }
            video->addCopy();
            _customerManager->getCustomer(customerId)
                ->returnVideo(video->getId());
            break;
        }
        case 4:
        {
            int id = 0;
            promptInt(id, "Enter the video ID: ");
            Video *video = _videoStore->getVideo(id);
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
            int count = _videoStore->getVideo(id)->getCopyCount();
            if (count > 0)
                std::cout << "Video is available.\n";
            else
                std::cout << "Video is not available.\n";
            break;
        }
        case 7:
            // TODO: Implement this
            break;
        case 8:
        {
        }
            std::cout << "\nThank you for using the program!\n\nMembers:\n";
            for (auto const &member : _members)
                std::cout << "- " << member[0] << ": " << member[1] << std::endl;
            std::cout << "\nThis program was brought to you by BMSCT\n-- Binary Marikina Shoe Company Tree --";
            break;
        }
    } while (selection != 8);
};

void Program::loadVideos() const
{
    std::ifstream file(_videosPath);
    std::string line = "";
    std::string title = "", genre = "", production = "";
    int copyCount = 0;
    Video *video = nullptr;
    while (std::getline(file, line))
    {
        promptString(title, "Title: ");
        promptString(genre, "Genre: ");
        promptString(production, "Production: ");
        promptInt(copyCount, "Copy Count: ");
        video = new Video(title, genre, production, copyCount);
        _videoStore->addVideo(video);
    }
    file.close();
    std::cout << "Videos loaded successfully!\n";
};

void Program::saveVideos(){
    // std::ofstream file(videosPath);
    // Video *video = _videoStore->getHead();
    // while (video != nullptr)
    // {
    //     file << video->getTitle() << "\n";
    //     file << video->getGenre() << "\n";
    //     file << video->getProduction() << "\n";
    //     file << video->getCopyCount() << "\n";
    //     video = video->getNext();
    // }
    // file.close();
    // std::cout << "Videos saved successfully!\n";
};

void Program::init()
{
    std::cout << "Welcome to the video store!" << std::endl;
    prompt();
}
