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
    for (auto const &choice : choices)
        std::cout << choice.first << ". " << choice.second << std::endl;
}
void Program::prompt() const
{
    Program::displayMenu();
    // int selection = -1;
    // try
    // {
    //     Program::promptChoices(selection, 6, "Enter your choice: ");
    //     switch (selection)
    //     {
    //     case 1:
    //         _videoStore->addVideo();
    //         break;
    //     case 2:
    //         _videoStore->rentVideo();
    //         break;
    //     case 3:
    //         _videoStore->returnVideo();
    //         break;
    //     case 4:
    //         _videoStore->getVideos();
    //         break;
    //     case 5:
    //         _videoStore->getVideo().getCopyCount();
    //         break;
    //     case 6:
            
    //     case 7:
    //         std::cout << "Exiting..." << std::endl;
    //         break;
    //     }
    // }
    // catch (const std::exception &e)
    // {
    //     std::cerr << e.what() << '\n';
    // }
}
void Program::promptChoices(int &selection, int max = 0, std::string message = "")
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
}
void Program::loadVideos() const
{
    // std::ifstream file(_paths.customers);
    // std::string line = "";
    // std::vector<Video> videos = {};
    // while (std::getline(file, line))
    // {
    //     std::getline(file, line);
    //     std::string title = line;
    //     std::getline(file, line);
    //     std::string genre = line;
    //     std::string production = line;
    //     std::getline(file, line);
    //     int copyCount = std::stoi(line);
    //     Video video = Video(title, genre, production, copyCount);
    //     videos.push_back(video);
    // }
    // *_videoStore = VideoStore(videos);
};
void Program::init() const
{
    std::cout << "Welcome to the video store!" << std::endl;
    Program::prompt();
}