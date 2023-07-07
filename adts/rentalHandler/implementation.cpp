#include <iostream>
#include <string>
#include <stack>
#include "data.hpp"

RentalHandler::RentalHandler(std::string rentalsPath)
{
    _savePath = rentalsPath;
    _ifstream.open(_savePath);
    if (!_ifstream.is_open())
    {
        std::cout << "Error: Unable to load rental data\n";
        return;
    }
    std::string line = "";
    int id = 0, customerId = 0, videoId = 0;
    while (std::getline(_ifstream, line))
    {
        id = std::stoi(line);
        std::getline(_ifstream, line);
        customerId = std::stoi(line);
        std::getline(_ifstream, line);
        videoId = std::stoi(line);
        Rental *rental = new Rental(id, customerId, videoId);
        _rentedVideos.push(rental);
    };
    _ifstream.close();
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
    _videoId = videoId;
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
int RentalHandler::Rental::getVideoId() const
{
    return _videoId;
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

void RentalHandler::rentVideo(int id, int customerId, int videoId)
{
    Rental *rental = new Rental(id, customerId, videoId);
    _rentedVideos.push(rental);
    std::cout << "Success: Rental added\n";
}

void RentalHandler::returnVideo(int customerId, int videoId)
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        if (rental->getCustomerId() == customerId && rental->getVideoId() == videoId)
        {
            delete rental;
            std::cout << "Info: Rental removed\n";
            _rentedVideos.pop();
            break;
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

void RentalHandler::displayCustomerRentals(int customerId)
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        if (rental->getCustomerId() == customerId)
        {
            std::cout << "Rental ID: " << rental->getId() << "\n";
            std::cout << "Customer ID: " << rental->getCustomerId() << "\n";
            std::cout << "Video IDs: " << rental->getVideoId() << "\n";
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

void RentalHandler::displayAllRentals()
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        std::cout << "Rental ID: " << rental->getId() << "\n";
        std::cout << "Customer ID: " << rental->getCustomerId() << "\n";
        std::cout << "Video IDs: " << rental->getVideoId() << "\n";
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
    if (!_ofstream.is_open())
    {
        std::cout << "Error: Unable to save rental data\n";
        return;
    }
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        _ofstream << rental->getId() << "\n";
        _ofstream << rental->getCustomerId() << "\n";
        _ofstream << rental->getVideoId() << "\n";
        temp.push(rental);
        _rentedVideos.pop();
    }

    while (!temp.empty())
    {
        _rentedVideos.push(temp.top());
        temp.pop();
    }
    _ofstream.close();
}

void RentalHandler::displayRentedVideos(int customerId)
{
    std::stack<Rental *> temp = {};
    while (!_rentedVideos.empty())
    {
        Rental *rental = _rentedVideos.top();
        if (rental->getCustomerId() == customerId)
        {
            std::cout << "Video ID: " << rental->getVideoId() << "\n";
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