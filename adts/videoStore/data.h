#pragma once
#include <map>
#include <vector>
#include <string>
#include <stack>
#include "../video/data.h"

class VideoStore
{
private:
    Video *_head = nullptr;
    Video *_tail = nullptr;
    Video *_curr = nullptr;
    std::stack<Video *> _rentedVideos = {};

public:
    VideoStore(){};
    ~VideoStore(){};
    Video *getVideo(int id) const;
    void addVideo(Video *video);
    int rentVideo(int id);
    void returnVideo(int id) const;
    Video* getHead() const;
    void displayVideos() const;
};