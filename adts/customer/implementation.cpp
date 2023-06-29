#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <fstream>
#include <queue>
#include "data.h"

BaseCustomer::BaseCustomer()
{
    _id++;
}

int BaseCustomer::getId() const
{
    return _id;
}

std::string BaseCustomer::getName() const
{
    return _name;
}

std::string BaseCustomer::getAddress() const
{
    return _address;
}
int BaseCustomer::_id = 0;

Customer::Customer(std::string name, std::string address) : BaseCustomer()
{
    _name = name;
    _address = address;
    _id++;
}

void Customer::rentVideo(int id)
{
    _rentedVideos.push(id);
}
void Customer::returnVideo(int id)
{
    if (_rentedVideos.size() == 0)
    {
        std::cout << "No videos rented" << std::endl;
        return;
    }
    std::stack<int> temp = {};
    while (_rentedVideos.size() != 0)
    {
        if (_rentedVideos.top() == id)
        {
            _rentedVideos.pop();
            std::cout << "Video successfully returned" << std::endl;
            return;
        }
        temp.push(_rentedVideos.top());
        _rentedVideos.pop();
    }
    while (temp.size() != 0)
    {
        _rentedVideos.push(temp.top());
        temp.pop();
    }
    std::cout << "Video not found" << std::endl;
}