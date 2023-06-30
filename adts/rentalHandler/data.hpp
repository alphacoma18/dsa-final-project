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
        static int _idCounter;
        int _id = 0;
        int _customerId = 0;
        std::stack<int> _videoIds = {};

    public:
        Rental(int customerId, int videoId);
        ~Rental();
        int getId() const;
        int getCustomerId() const;
        std::stack<int> getVideoIds() const;
        void addVideo(int videoId);
        void removeVideo(int videoId);
    };
    std::stack<Rental *> _rentedVideos = {};
    std::string _filename = "rentals.txt";
    std::ofstream _ofstream = {};
    std::ifstream _ifstream = {};
    Rental *getRental(int id);

public:
    RentalHandler();
    ~RentalHandler();
    void addRental(int customerId, int videoId);
    void rentVideo(int customerId, int videoId);
    void returnVideo(int customerId, int videoId);
    void displayCustomerRentals(int customerId);
    void displayAllRentals();
    void saveRentals();
};