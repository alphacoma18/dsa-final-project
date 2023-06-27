#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

VideoStore::VideoStore(){};

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
}
void VideoStore::addVideo(Video video)
{
    if (_head == nullptr)
    {
        _head = new Video(video.getTitle(), video.getGenre(), video.getProduction(), video.getCopyCount());
        _tail = _head;
    }
    else
    {
        Video *newVideo = new Video(video.getTitle(), video.getGenre(), video.getProduction(), video.getCopyCount());
        _tail->setNext(newVideo);
        newVideo->setPrev(_tail);
        _tail = newVideo;
    }
    std::cout << "Video successfully added" << std::endl;
}

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
}

void VideoStore::getVideos() const
{
    Video *curr = _head;
    while (curr != nullptr)
    {
        std::cout << "Video ID: " << curr->getId() << std::endl;
        std::cout << "Title: " << curr->getTitle() << std::endl;
        std::cout << "Genre: " << curr->getGenre() << std::endl;
        std::cout << "Copies: " << curr->getCopyCount() << std::endl;
        curr = curr->getNext();
    }
}