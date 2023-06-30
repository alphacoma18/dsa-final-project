#pragma once
#include <string>
#include <queue>

class CustomerHandler
{
private:
    class Customer
    {
    private:
        static int _id;
        std::string _name = "";
        std::string _address = "";

    public:
        Customer(std::string name, std::string address);
        ~Customer();
        int getId() const;
        std::string getName() const;
        std::string getAddress() const;
    };
    std::queue<Customer *> _customers = {};

public:
    CustomerHandler();
    ~CustomerHandler();
    Customer *getCustomer(int id);
    bool customerExists(int id);
    void addCustomer(std::string name, std::string address);
    void displayCustomers() const;
    void displayCustomerDetails(int id);
    void saveCustomerDetails() const;
};
