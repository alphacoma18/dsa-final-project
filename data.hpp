#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include "./adts/videoStore/data.hpp"
#include "./adts/customerHandler/data.hpp"
#include "./adts/rentalHandler/data.hpp"

class BaseProgram
{
protected:
    std::string _videosPath = "videos.txt";
    const std::vector<std::vector<std::string>> _members = {
        {"Alpha Romer Coma", "Lead Programmer"},
        {"Raphael Andre Mercado", "Programmer 1"},
        {"Rab Karl Colasino", "Programmer 2"},
        {"Justine Mae Celestial", "QA & Documentation"},
        {"Enrico Casas", "QA & Documentation"}};
    void promptInt(int &input, std::string message) const;
    void promptString(std::string &input, std::string message) const;
    void promptChoices(int &selection, int max, std::string message) const;
};
class Program : public BaseProgram
{
private:
    std::map<int, std::string> _choices = {
        {1, "New Video"},
        {2, "Rent a Video"},
        {3, "Return a Video"},
        {4, "Show Video Details"},
        {5, "Display all Videos"},
        {6, "Check Video Availability"},
        {7, "Customer Maintenance"},
        {8, "Exit"}};
    std::map<int, std::string> _customerChoices = {
        {1, "Add Customer"},
        {2, "Show Customer Details"},
        {3, "List of videos rented by customer"},
        {4, "Back"}};

    VideoStore *_videoStore = new VideoStore(_videosPath);
    CustomerHandler *_customerHandler = new CustomerHandler();
    RentalHandler *_rentalHandler = new RentalHandler();
    void loadVideos() const;
    void prompt();
    void displayMenu() const;
    void saveVideos();
    void saveCustomers();
    void saveRentals();

public:
    Program();
    ~Program();
    void init();
};