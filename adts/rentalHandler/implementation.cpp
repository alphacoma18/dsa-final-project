#include <iostream>
#include <string>
#include <stack>
#include "data.hpp"

RentalHandler::RentalHandler(std::string rentalsPath){
    // _savePath = rentalsPath;
    // _ifstream.open(_savePath);
    // if (!_ifstream.is_open())
    // {
    //     std::cout << "Info: No rental data found\n";
    //     return;
    // }
    // std::string line = "";
    // int id = 0, customerId = 0, videoId = 0;
    // // Line 1 : id
    // // Line 2 : customer id
    // //  Line 3 : Video_ID(of all rented videos of a customer)

    // while (std::getline(_ifstream, line))
    // {
    //     id = std::stoi(line);
    //     std::getline(_ifstream, line);
    //     customerId = std::stoi(line);
    //     Rental *rental = new Rental(id, customerId, videoId);
    //     while (std::getline(_ifstream, line))
    //     {
    //         if (line == "")
    //             break;
    //         videoId = std::stoi(line);
    //         rental->addVideo(videoId);
    //     }
    //     _rentedVideos.push(rental);
    // };
    // _ifstream.close();
};
RentalHandler::~RentalHandler()
{
    while (!_rentedVideos.empty())
    {
        delete _rentedVideos.top();
        _rentedVideos.pop();
    }
};
RentalHandler::Rental::Rental(int id, int customerId, int videoId)
{
    _id = id;
    _customerId = customerId;
    _videoIds.push(videoId);
}
RentalHandler::Rental::~Rental() = default;
int RentalHandler::Rental::getId() const
{
    return _id;
}

int RentalHandler::Rental::getCustomerId() const
{
    return _customerId;
}
std::stack<int> RentalHandler::Rental::getVideoIds() const
{
    return _videoIds;
}

void RentalHandler::Rental::addVideo(int videoId)
{
    _videoIds.push(videoId);
}

void RentalHandler::Rental::removeVideo(int videoId)
{
    std::stack<int> temp = {};
    while (!_videoIds.empty())
    {
        if (_videoIds.top() != videoId)
        {
            temp.push(_videoIds.top());
        }
        _videoIds.pop();
    }
    while (!temp.empty())
    {
        _videoIds.push(temp.top());
        temp.pop();
    }
}

RentalHandler::Rental *RentalHandler::getRental(int id)
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        if (rental->getId() == id)
        {
            return rental;
        }
        temp.push(rental);
        _rentedVideos.pop();
    }
    while (!temp.empty())
    {
        _rentedVideos.push(temp.top());
        temp.pop();
    }
    std::cout << "Info: Rental not found\n";
    return nullptr;
}

void RentalHandler::addRental(int id, int customerId, int videoId)
{
    Rental *rental = new Rental(id, customerId, videoId);
    _rentedVideos.push(rental);
    std::cout << "Response: Rental Successfully Added\n";
}

void RentalHandler::rentVideo(int customerId, int videoId)
{
    Rental *rental = getRental(customerId);
    if (rental == nullptr)
        return;
    rental->addVideo(videoId);
    std::cout << "Response: Video Successfully Rented\n";
}

void RentalHandler::returnVideo(int customerId, int videoId)
{
    Rental *rental = getRental(customerId);
    if (rental == nullptr)
        return;
    rental->removeVideo(videoId);
    std::cout << "Response: Video Successfully Returned\n";
}

void RentalHandler::displayCustomerRentals(int customerId)
{
    Rental *rental = getRental(customerId);
    if (rental == nullptr)
        return;
    std::stack<int> videoIds = rental->getVideoIds();
    while (!videoIds.empty())
    {
        std::cout << videoIds.top() << "\n";
        videoIds.pop();
    }
}

void RentalHandler::displayAllRentals()
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        std::cout << rental->getCustomerId() << "\n";
        std::stack<int> videoIds = rental->getVideoIds();
        while (!videoIds.empty())
        {
            std::cout << videoIds.top() << "\n";
            videoIds.pop();
        }
        temp.push(rental);
        _rentedVideos.pop();
    }
    while (!temp.empty())
    {
        _rentedVideos.push(temp.top());
        temp.pop();
    }
}

void RentalHandler::saveRentals()
{
    _ofstream.open(_savePath);
    std::stack<Rental *> temp = {};

    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        _ofstream << rental->getId() << " " << rental->getCustomerId() << "\n";
        std::stack<int> videoIds = rental->getVideoIds();
        while (!videoIds.empty())
        {
            _ofstream << videoIds.top() << " ";
            videoIds.pop();
        }
        temp.push(rental);
        _rentedVideos.pop();
        _ofstream << "\n";
    }
    while (!temp.empty())
    {
        _rentedVideos.push(temp.top());
        temp.pop();
    }
    _ofstream.close();
}