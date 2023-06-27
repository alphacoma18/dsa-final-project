#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "./adts/videoStore/data.h"

class Program
{
private:
    std::map<int, std::string> choices = {
        {1, "New Video"},
        {2, "Rent a Video"},
        {3, "Return a Video"},
        {4, "Show Video Details"},
        {5, "Display all Videos"},
        {6, "Check Video Availability"},
        {7, "Customer Maintenance"},
        {8, "Exit"}};
    struct paths
    {
        std::string videos = "videos.txt";
        std::string customers = "customers.txt";
        std::string rentals = "rentals.txt";
    };
    paths _paths = paths{};
    VideoStore *_videoStore = nullptr;

    void loadVideos() const;
    void promptChoices(int &selection, int max, std::string message);
    void prompt() const;
    void displayMenu() const;

public:
    Program();
    ~Program();
    void init() const;
};