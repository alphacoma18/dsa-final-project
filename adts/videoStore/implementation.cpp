#include <string>
#include <iostream>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.hpp"

VideoStore::Video::Video(std::string title, std::string genre, std::string production, int copyCount) : _title(title), _genre(genre), _production(production), _copyCount(copyCount)
{
    _id = ++_idCounter;
}

VideoStore::Video::~Video()
{
    _idCounter--;
}

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
int VideoStore::Video::_idCounter = 0;

VideoStore::VideoStore(std::string &videosPath)
{
    std::ifstream file(videosPath);
    std::string line = "", title = "", genre = "", production = "";
    int copyCount = 0;
    while (std::getline(file, line))
    {
    }
    file.close();
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
