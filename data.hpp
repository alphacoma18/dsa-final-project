#pragma once
#include <string>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include "./adts/videoStore/data.hpp"
#include "./adts/customerHandler/data.hpp"
#include "./adts/rentalHandler/data.hpp"

class BaseProgram
{
protected:
    struct Paths
    {
        std::string videos = "./data/videos.txt";
        std::string customers = "./data/customers.txt";
        std::string rentals = "./data/customer-rent.txt";
        std::string persist = "./data/_persist.txt";
    };
    const Paths _paths = Paths();
    struct Ids
    {
        int videoId = 0;
        int customerId = 0;
        int rentalId = 0;
    };
    Ids _ids = Ids();
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

    VideoStore *_videoStore = new VideoStore(_paths.videos);
    CustomerHandler *_customerHandler = new CustomerHandler(_paths.customers);
    RentalHandler *_rentalHandler = new RentalHandler(_paths.rentals);
    std::ofstream _ofstream = {};
    std::ifstream _ifstream = {};


    void loadVideos() const;
    void prompt();
    void displayMenu() const;
    void saveVideos();
    void saveCustomers();
    void saveRentals();
    void displayCustomerM() const;

public:
    Program();
    ~Program();
    void init();
};