#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "./adts/videoStore/data.h"
// #include "./adts/videoStore/implementation.cpp"
// #include "./adts/customerManager/data.h"
// #include "./adts/customer/implementation.cpp"

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
    std::string videosPath = "videos.txt";
    VideoStore *_videoStore = new VideoStore();
    // CustomerManager *_processAccount = new CustomerManager();
    const std::vector<std::string> _members = {"Alpha Romer Coma", "Mercado Raphael Andre", "Rab Karl Colasino", "Justine Celestial", "Enrico Casas"};
    void promptInt(int &input, std::string message) const;
    void promptString(std::string &input, std::string message) const;
    void promptChoices(int &selection, int max, std::string message) const;
    // void loadVideos() const;
    void prompt() const;
    void displayMenu() const;

public:
    Program(){};
    ~Program(){};
    void init();
};