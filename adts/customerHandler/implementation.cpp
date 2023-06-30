#include <iostream>
#include <string>
#include "data.hpp"

CustomerHandler::Customer::Customer(std::string name, std::string address)
{
    _id++;
    _name = name;
    _address = address;
}

CustomerHandler::Customer::~Customer() = default;

int CustomerHandler::Customer::getId() const
{
    return _id;
}

std::string CustomerHandler::Customer::getName() const
{
    return _name;
}

std::string CustomerHandler::Customer::getAddress() const
{
    return _address;
}

int CustomerHandler::Customer::_id = 0;

CustomerHandler::CustomerHandler() = default;

CustomerHandler::~CustomerHandler() {
    while (!_customers.empty())
    {
        Customer *customer = _customers.front();
        _customers.pop();
        delete customer;
    }
};

CustomerHandler::Customer *CustomerHandler::getCustomer(int id)
{
    std::queue<Customer *> customerQueue = _customers;
    while (!customerQueue.empty())
    {
        Customer *customer = customerQueue.front();
        if (customer->getId() == id)
            return customer;
        customerQueue.pop();
    }
    return nullptr;
}

bool CustomerHandler::customerExists(int id)
{
    Customer *customer = getCustomer(id);
    if (customer == nullptr)
        return false;
    return true;
}

void CustomerHandler::addCustomer(std::string name, std::string address)
{
    Customer *customer = new Customer(name, address);
    _customers.push(customer);
    std::cout << "Response: Customer Successfully Added\n";
}

void CustomerHandler::displayCustomers() const
{
    std::queue<Customer *> customerQueue = _customers;
    if (customerQueue.empty())
    {
        std::cout << "Info: No customers in queue\n";
        return;
    }
    while (!customerQueue.empty())
    {
        Customer *customer = customerQueue.front();
        std::cout << "-------------------------\n";
        std::cout << "Customer ID" << customer->getId() << "\n";
        std::cout << "Name: " << customer->getName() << "\n";
        std::cout << "Address: " << customer->getAddress() << "\n";
        std::cout << "-------------------------\n";
        customerQueue.pop();
    }
}

void CustomerHandler::displayCustomerDetails(int id)
{
    Customer *customer = getCustomer(id);
    if (customer == nullptr)
        return;
    std::cout << "-------------------------\n";
    std::cout << "Customer ID" << customer->getId() << "\n";
    std::cout << "Name: " << customer->getName() << "\n";
    std::cout << "Address: " << customer->getAddress() << "\n";
    std::cout << "-------------------------\n";
}
