#pragma once
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <queue>
#include <stack>

class BaseCustomer
{
protected:
    static int _id;
    std::string _name = "";
    std::string _address = "";
    int customerCount = 0;

public:
    BaseCustomer();
    int getId() const;
    std::string getName() const;
    std::string getAddress() const;
};

class Customer : public BaseCustomer
{
private:
    std::stack<int> _rentedVideos = {};

public:
    Customer(std::string name, std::string address);
    void rentVideo(int id);
    void returnVideo(int id);
};

class processAccount
{
private:
    std::string _customerPath = "customers.txt";
    std::string _rentalPath = "rentals.txt";
    std::queue<Customer *>
        _customerQueue = {};
    bool _isEmpty() const;
    int _customerCount();

public:
    Customer *getCustomer(int id);
    std::string getCustomerPath() const;
    std::string getRentalPath() const;
    void addCustomer(std::string name, std::string address);
    void printCustomerDetails(int customerID);
    void saveCustomerDetails();
};