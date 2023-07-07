#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.hpp"

VideoStore::Video::Video(int id, std::string title, std::string genre, std::string production, int copyCount) : _id(id), _title(title), _genre(genre), _production(production), _copyCount(copyCount){};

VideoStore::Video::~Video() = default;

int VideoStore::Video::getId() const
{
    return _id;
}

std::string VideoStore::Video::getTitle() const
{
    return _title;
}
std::string VideoStore::Video::getGenre() const
{
    return _genre;
}
std::string VideoStore::Video::getProduction() const
{
    return _production;
}

int VideoStore::Video::getCopyCount() const
{
    return _copyCount;
}

void VideoStore::Video::addCopy()
{
    ++_copyCount;
}
void VideoStore::Video::removeCopy()
{
    --_copyCount;
}
VideoStore::Video *VideoStore::Video::getNext() const
{
    return _next;
}
VideoStore::Video *VideoStore::Video::getPrev() const
{
    return _prev;
}
void VideoStore::Video::setNext(Video *next)
{
    _next = next;
}
void VideoStore::Video::setPrev(Video *prev)
{
    _prev = prev;
}

VideoStore::VideoStore(std::string videosPath)
{
    _savePath = videosPath;
    _ifstream.open(_savePath);
    if (!_ifstream.is_open())
    {
        std::cout << "Error: Unable to load video data\n";
        return;
    }
    std::string line = "", title = "", genre = "", production = "";
    int id = 0, copyCount = 0;
    while (std::getline(_ifstream, line))
    {
        id = std::stoi(line);
        std::getline(_ifstream, title);
        std::getline(_ifstream, genre);
        std::getline(_ifstream, production);
        std::getline(_ifstream, line);
        copyCount = std::stoi(line);
        std::getline(_ifstream, line);
        addVideo(new Video(id, title, genre, production, copyCount));
    }
    _ifstream.close();
};

VideoStore::~VideoStore()
{
    Video *curr = _head;
    while (curr != nullptr)
    {
        Video *next = curr->getNext();
        delete curr;
        curr = next;
    }

    _head = nullptr;
    _tail = nullptr;
    _curr = nullptr;
};

VideoStore::Video *VideoStore::getVideo(int id) const
{
    Video *curr = _head;
    while (curr != nullptr)
    {
        if (curr->getId() == id)
            return curr;
        curr = curr->getNext();
    }
    return nullptr;
};

bool VideoStore::videoExists(int id) const
{
    Video *video = getVideo(id);
    if (video == nullptr)
        return false;
    return true;
};

void VideoStore::addVideo(Video *video)
{
    if (_head == nullptr)
    {
        _head = video;
        _tail = video;
        return;
    }
    _tail->setNext(video);
    video->setPrev(_tail);
    _tail = video;
};

VideoStore::Video *VideoStore::rentVideo(int id)
{
    Video *video = getVideo(id);
    if (video == nullptr)
        return nullptr;
    if (video->getCopyCount() == 0)
    {
        std::cout << "Info: No copies available\n";
        return nullptr;
    }
    video->removeCopy();
    return video;
};

VideoStore::Video *VideoStore::returnVideo(int id) const
{
    Video *video = getVideo(id);
    if (video == nullptr)
        return nullptr;
    video->addCopy();
    std::cout << "Success: Video returned\n";
    return video;
};
VideoStore::Video *VideoStore::getHead() const
{
    return _head;
};
void VideoStore::displayVideos() const
{
    Video *curr = _head;
    if (curr == nullptr)
    {
        std::cout << "\nInfo: No videos available\n";
        return;
    }
    std::cout << "\n------------------ Videos ------------------\n\n";
    while (curr != nullptr)
    {
        std::cout << "ID: " << curr->getId() << "\n";
        std::cout << "Title: " << curr->getTitle() << "\n";
        std::cout << "Genre: " << curr->getGenre() << "\n";
        std::cout << "Production: " << curr->getProduction() << "\n";
        std::cout << "Copy Count: " << curr->getCopyCount() << "\n\n";
        curr = curr->getNext();
    }
};

void VideoStore::saveVideos() const
{
    std::ofstream outputFile(_savePath);
    if (!outputFile.is_open())
    {
        std::cout << "Error: Unable to save video data\n";
        return;
    }
    Video *curr = _head;
    while (curr != nullptr)
    {
        outputFile << curr->getId() << "\n";
        outputFile << curr->getTitle() << "\n";
        outputFile << curr->getGenre() << "\n";
        outputFile << curr->getProduction() << "\n";
        outputFile << curr->getCopyCount() << "\n\n";
        curr = curr->getNext();
    }
    outputFile.close();
    std::cout << "Success: Videos saved.\n";
}