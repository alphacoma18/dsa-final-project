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

// git save ko lang
//san mo balak ung inputs ilagay main?
// mayroon sa Program class

void Customer::rentVideo(int id)
{
    // TODO videoStore
    _rentedVideos.push(id);
}
std::string processAccount::getCustomerPath() const
{
    return _customerPath;
}
std::string processAccount::getRentalPath() const
{
    return _rentalPath;
}
Customer *processAccount::getCustomer(int id)
{
    if (_customerQueue.size() == 0)
    {
        std::cout << "No customers in queue" << std::endl;
        return nullptr;
    }
    Customer *customer = _customerQueue.front();
    // TODO
}
void processAccount::addCustomer(std::string name, std::string address)
{
    Customer *customer = new Customer(name, address);
    _customerQueue.push(customer);
    std::cout << "Customer Successfully Added" << std::endl;
}

void processAccount::printCustomerDetails(int customerId)
{
    Customer *customer = getCustomer(customerId);
    if (customer == nullptr)
        return;
    std::cout << "-------------------------" << std::endl;
    std::cout << "Customer ID" << customer->getId() << std::endl;
    std::cout << "Name: " << customer->getName() << std::endl;
    std::cout << "Address: " << customer->getAddress() << std::endl;
    std::cout << "-------------------------" << std::endl;
}

void processAccount::saveCustomerDetails()
{
    std::ofstream outputFile(getCustomerPath());
    if (outputFile.is_open())
    {
        Customer *customer = getCustomer(0);
        while (customer != nullptr)
        {
            outputFile << "-------------------------" << std::endl;
            outputFile << "Customer ID" << customer->getId() << std::endl;
            outputFile << "Name: " << customer->getName() << std::endl;
            outputFile << "Address: " << customer->getAddress() << std::endl;
            outputFile << "-------------------------" << std::endl;
            customer = getCustomer(customer->getId());
        }
        outputFile.close();
    }
    else
    {
        std::cout << "File cannot be opened or missing." << std::endl;
    }
}