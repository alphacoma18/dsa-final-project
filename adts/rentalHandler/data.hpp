#pragma once
#include <string>
#include <stack>
#include <fstream>

class RentalHandler
{
private:
    class Rental
    {
    private:
        int _id = 0;
        int _customerId = 0;
        int _videoId = 0;

    public:
        Rental(int id, int customerId, int videoId);
        ~Rental();
        int getId() const;
        int getCustomerId() const;
        int getVideoId() const;
    };
    std::stack<Rental *> _rentedVideos = {};
    std::string _savePath = "";
    std::ofstream _ofstream = {};
    std::ifstream _ifstream = {};
    Rental *getRental(int id);

public:
    RentalHandler(std::string savePath);
    ~RentalHandler();
    void rentVideo(int id, int customerId, int videoId);
    void returnVideo(int customerId, int videoId);
    void displayCustomerRentals(int customerId);
    void displayAllRentals();
    void saveRentals();
    void displayRentedVideos(int customerId);
};