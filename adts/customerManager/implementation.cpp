#include <iostream>
#include <fstream>
#include "data.h"

// CustomerManager::CustomerManager() = default;
// CustomerManager::~CustomerManager() = default;

std::string CustomerManager::getCustomerPath() const
{
    return _customerPath;
}
std::string CustomerManager::getRentalPath() const
{
    return _rentalPath;
}
Customer *CustomerManager::getCustomer(int id)
{
    if (_customerQueue.empty())
    {
        std::cout << "No customers in queue" << std::endl;
        return nullptr;
    }
    
    Customer *customer = _customerQueue.front();
    if (customer->getId() == id)
    {
        _customerQueue.pop();
        return customer;
    }
    else
    {
        _customerQueue.pop();
        _customerQueue.push(customer);
        return getCustomer(id);
    }
    
}

void CustomerManager::addCustomer(std::string name, std::string address)
{
    Customer *customer = new Customer(name, address);
    _customerQueue.push(customer);
    std::cout << "Customer Successfully Added" << std::endl;
}

void CustomerManager::printCustomerDetails(int customerId)
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

void CustomerManager::saveCustomerDetails()
{
    std::ofstream outputFile(getCustomerPath());
     if (outputFile.is_open())
    {
        Customer *customer = getCustomer(0);
        while (customer != nullptr)
        {
            outputFile << "-------------------------" << std::endl;
            outputFile << "Customer ID" << customer->getId() << std::endl;
  
    std::ofstream outputFile(getCustomerPath());
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