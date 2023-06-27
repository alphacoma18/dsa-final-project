#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>
#include <fstream>
#include "data.h"

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