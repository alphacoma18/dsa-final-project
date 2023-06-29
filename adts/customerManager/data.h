#pragma once
#include <string>
#include <queue>
#include "../customer/data.h"

class CustomerManager
{
private:
    std::string _customerPath = "customers.txt";
    std::string _rentalPath = "rentals.txt";
    std::queue<Customer *>
        _customerQueue = {};
    bool _isEmpty() const;
    int _customerCount() const;

public:
    CustomerManager() = default;
    ~CustomerManager() = default;
    Customer *getCustomer(int id);
    std::string getCustomerPath() const;
    std::string getRentalPath() const;
    void addCustomer(std::string name, std::string address);
    void printCustomerDetails(int customerID);
    void saveCustomerDetails();
};