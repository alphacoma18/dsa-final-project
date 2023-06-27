#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

Video::Video(std::string title, std::string genre, std::string production, int copyCount) : _title(title), _genre(genre), _production(production), copyCount(copyCount)
{
    _id = ++_idCounter;
}

int Video::getId() const
{
    return _id;
}

std::string Video::getTitle() const
{
    return _title;
}
std::string Video::getGenre() const
{
    return _genre;
}
std::string Video::getProduction() const
{
    return _production;
}

int Video::getCopyCount() const
{
    return copyCount;
}

void Video::addCopy()
{
    ++copyCount;
}

void Video::removeCopy()
{
    --copyCount;
};

VideoStore::VideoStore(std::vector<Video> videos)
{
    for (auto const &video : videos)
        _videoMap.insert(std::pair<int, Video>(video.getId(), video));
}
Video VideoStore::getVideo(int id) const
{
    try
    {
        return _videoMap.at(id);
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Video with id " << id << " not found." << std::endl;
    }
}
void VideoStore::addVideo(Video video)
{
    _videoMap.insert(std::pair<int, Video>(video.getId(), video));
}

int VideoStore::rentVideo(int id)
{
    Video video = VideoStore::getVideo(id);
    const bool copyExists = video.getCopyCount() > 0;
    if (!copyExists)
    {
        std::cout << "No more copies of " << video.getTitle() << " available." << std::endl;
        return -1;
    }
    video.removeCopy();
    std::cout << "Successfully rented " << video.getTitle() << "." << std::endl;
    return video.getId();
}

void VideoStore::returnVideo(int id) const
{
    try
    {
        Video video = VideoStore::getVideo(id);
        video.addCopy();
    }
    catch (const std::out_of_range &e)
    {
        std::cout << "Video with id " << id << " not found." << std::endl;
    }
}

void VideoStore::getVideos() const
{
    for (auto const &video : _videoMap)
        std::cout << video.second.getTitle() << " (" << video.second.getProduction() << ") - " << video.second.getCopyCount() << " copies available." << std::endl;
}

class BaseCustomer
{
protected:
    static int _id;
    std::string _name = "";
    std::string _address = "";
};

class Customer : public BaseCustomer
{
private:
    std::vector<int> _rentedVideos = {};

public:
    Customer(std::string name, std::string address) : BaseCustomer()
    {
        _name = name;
        _address = address;
        _id++;
    }
    void rentVideo(int id)
    {
        _rentedVideos.push_back(id);
    }
    void returnVideo(int id)
    {
        _rentedVideos.erase(std::remove(_rentedVideos.begin(), _rentedVideos.end(), id), _rentedVideos.end());
    }
};

int Video::_idCounter = 0;
int BaseCustomer::_id = 0;
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
    int selection = -1;
    try
    {
        Program::promptChoices(selection, 6, "Enter your choice: ");
        switch (selection)
        {
        case 1:
            _videoStore->addVideo();
            break;
        case 2:
            _videoStore->rentVideo();
            break;
        case 3:
            _videoStore->returnVideo();
            break;
        case 4:
            _videoStore->getVideos();
            break;
        case 5:
            // pass id
            _videoStore->getVideo().getCopyCount();
            break;
        case 6:
            
        case 7:
            std::cout << "Exiting..." << std::endl;
            break;
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
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
    std::ifstream file(_paths.customers);
    std::string line = "";
    std::vector<Video> videos = {};
    while (std::getline(file, line))
    {
        std::getline(file, line);
        std::string title = line;
        std::getline(file, line);
        std::string genre = line;
        std::string production = line;
        std::getline(file, line);
        int copyCount = std::stoi(line);
        Video video = Video(title, genre, production, copyCount);
        videos.push_back(video);
    }
    *_videoStore = VideoStore(videos);
};
void Program::init() const
{
    std::cout << "Welcome to the video store!" << std::endl;
    Program::prompt();
}