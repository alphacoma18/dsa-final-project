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
    int _customerCount = 0;

public:
    CustomerManager(){};
    ~CustomerManager(){};
    Customer *getCustomer(int id);
    std::string getCustomerPath() const;
    std::string getRentalPath() const;
    void addCustomer(std::string name, std::string address);
    void printCustomerDetails(int customerID);
    void saveCustomerDetails();
};