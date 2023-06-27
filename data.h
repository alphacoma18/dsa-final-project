#include <string>
#include <map>
#include <vector>
#include <algorithm>

class Video
{
private:
    static int _idCounter;
    int _id = 0;
    const std::string _title = "";
    const std::string _genre = "";
    const std::string _production = "";
    int copyCount = 0;

public:
    Video(std::string title, std::string genre, std::string production, int copyCount = 1);
    int getId() const;
    std::string getTitle() const;
    std::string getGenre() const;
    std::string getProduction() const;
    int getCopyCount() const;
    void addCopy();
    void removeCopy();
};

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