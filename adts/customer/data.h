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

public:
    BaseCustomer();
    virtual ~BaseCustomer();
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