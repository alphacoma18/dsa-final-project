#pragma once
#include <map>
#include <vector>
#include "../video/data.h"
#include <string>
#include <stack>
class VideoStore
{
private:
    Video *_head = nullptr;
    Video *_tail = nullptr;
    Video *_curr = nullptr;
    std::stack<Video *> _rentedVideos = {};

public:
    VideoStore();
    Video *getVideo(int id) const;
    void addVideo(Video video);
    int rentVideo(int id);
    void returnVideo(int id) const;
    void getVideos() const;
};