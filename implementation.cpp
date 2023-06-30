#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.hpp"

void BaseProgram::promptChoices(int &selection, int max, std::string message) const
{
    try
    {
        std::cout << message;
        std::cin >> selection;
        if (selection < 0 || selection > max || std::cin.fail())
            throw std::invalid_argument("Error: Invalid input.");
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
        if (input < 0 || std::cin.fail())
            throw std::invalid_argument("Error: Invalid input.");
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
        if (input.empty() || std::cin.fail())
            throw std::invalid_argument("Error: Invalid input.");
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        promptString(input, message);
    }
};

Program::Program() = default;
Program::~Program() {
    delete _videoStore;
    delete _customerHandler;
    delete _rentalHandler;
};

void Program::displayMenu() const
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
            // _videoStore->addVideo(Video(title, genre, production, copyCount));
            // _videoStore->addVideo(video);
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
            // TODO: Implement this
            break;
        case 8:
        {
            saveVideos();
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

void Program::loadVideos() const
{
    std::ifstream file(_videosPath);
    std::string line = "";
    std::string title = "", genre = "", production = "";
    int copyCount = 0;
    VideoStore::Video *video = nullptr;
    while (std::getline(file, line))
    {
        promptString(title, "Title: ");
        promptString(genre, "Genre: ");
        promptString(production, "Production: ");
        promptInt(copyCount, "Copy Count: ");
        video = new VideoStore::Video(title, genre, production, copyCount);
        _videoStore->addVideo(video);
    }
    delete video;
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
void saveCustomers();

void Program::init()
{
    std::cout << "Welcome to the video store!\n";
    prompt();
}
