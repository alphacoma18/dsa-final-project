#include <map>
#include <vector>
#include "../video/data.h"
#include <string>

class VideoStore
{
private:
    std::map<int, Video> _videoMap = {};

public:
    VideoStore(std::vector<Video> videos);
    Video getVideo(int id) const;
    void addVideo(Video video);
    int rentVideo(int id);
    void returnVideo(int id) const;
    void getVideos() const;
};