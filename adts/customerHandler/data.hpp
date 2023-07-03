#pragma once
#include <string>
#include <queue>
#include <fstream>

class CustomerHandler
{
private:
    class Customer
    {
    private:
        int _id = 0;
        std::string _name = "";
        std::string _address = "";

    public:
        Customer(int id, std::string name, std::string address);
        ~Customer();
        int getId() const;
        std::string getName() const;
        std::string getAddress() const;
    };
    std::queue<Customer *> _customers = {};
    std::string _savePath = "";
    std::ofstream _ofstream = {};
    std::ifstream _ifstream = {};

public:
    CustomerHandler(std::string savePath);
    ~CustomerHandler();
    Customer *getCustomer(int id);
    bool customerExists(int id);
    void addCustomer(int id, std::string name, std::string address);
    void displayCustomers() const;
    void displayCustomerDetails(int id);
    void saveCustomerDetails() const;
};
