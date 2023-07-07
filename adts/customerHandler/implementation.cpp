#include <iostream>
#include <string>
#include "data.hpp"

CustomerHandler::Customer::Customer(int id, std::string name, std::string address)
{
    _id = id;
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

CustomerHandler::CustomerHandler(std::string savePath)
{
    _savePath = savePath;
    _ifstream.open(_savePath);
    if (!_ifstream.is_open())
    {
        std::cout << "Error: Unable to load customer data\n";
        return;
    }
    std::string line = "", name = "", address = "";
    int id = 0;
    while (std::getline(_ifstream, line))
    {
        id = std::stoi(line);
        std::getline(_ifstream, name);
        std::getline(_ifstream, address);
        Customer *customer = new Customer(id, name, address);
        _customers.push(customer);
        std::getline(_ifstream, line);
    };
    _ifstream.close();
}

CustomerHandler::~CustomerHandler()
{
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

void CustomerHandler::addCustomer(int id, std::string name, std::string address)
{
    Customer *customer = new Customer(id, name, address);
    _customers.push(customer);
    std::cout << "Success:" << name << " Customer Added\n";
}

void CustomerHandler::displayCustomers() const
{
    std::queue<Customer *> customerQueue = _customers;
    if (customerQueue.empty())
    {
        std::cout << "Info: No customers in queue\n";
        return;
    }
    std::cout << "\n------------------ Customers ------------------\n\n";
    while (!customerQueue.empty())
    {
        Customer *customer = customerQueue.front();
        std::cout << "Customer ID: " << customer->getId() << "\n";
        std::cout << "Name: " << customer->getName() << "\n";
        std::cout << "Address: " << customer->getAddress() << "\n\n";
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
void CustomerHandler::saveCustomers() const
{
    std::ofstream outputFile(_savePath);
    if (!outputFile.is_open())
    {
        std::cout << "Error: Unable to save customer data\n";
        return;
    }
    std::queue<Customer *> customerQueue = _customers;
    while (!customerQueue.empty())
    {
        Customer *customer = customerQueue.front();
        outputFile << customer->getId() << "\n";
        outputFile << customer->getName() << "\n";
        outputFile << customer->getAddress() << "\n\n";
        customerQueue.pop();
    }
    outputFile.close();
    std::cout << "Success: Customers saved.\n";
}
