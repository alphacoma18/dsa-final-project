#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

// VideoStore::VideoStore() = default;
// VideoStore::~VideoStore() = default;

Video *VideoStore::getVideo(int id) const
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

int VideoStore::rentVideo(int id)
{
    Video *video = getVideo(id);
    if (video == nullptr)
    {
        std::cout << "Video not found" << std::endl;
        return -1;
    }
    if (video->getCopyCount() == 0)
    {
        std::cout << "No copies available" << std::endl;
        return -1;
    }
    video->removeCopy();
    _rentedVideos.push(video);
    std::cout << "Video successfully rented" << std::endl;
    return video->getId();
};

void VideoStore::returnVideo(int id) const
{
    Video *video = getVideo(id);
    if (video == nullptr)
    {
        std::cout << "Video not found" << std::endl;
        return;
    }
    video->addCopy();
    std::cout << "Video successfully returned" << std::endl;
};
Video *VideoStore::getHead() const
{
    return _head;
};
void VideoStore::displayVideos() const
{
    Video *curr = _head;
    while (curr != nullptr)
    {
        std::cout << "ID: " << curr->getId() << std::endl;
        std::cout << "Title: " << curr->getTitle() << std::endl;
        std::cout << "Genre: " << curr->getGenre() << std::endl;
        std::cout << "Production: " << curr->getProduction() << std::endl;
        std::cout << "Copy Count: " << curr->getCopyCount() << std::endl;
        std::cout << std::endl;
        curr = curr->getNext();
    }
};