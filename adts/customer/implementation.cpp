#include <iostream>
#include <map>
#include <string>
#include <vector>
#include "data.h"

Customer::Customer(std::string name, std::string address) : BaseCustomer()
{
    _name = name;
    _address = address;
    _id++;
}
int BaseCustomer::_id = 0;

void processAccount::addCustomer(std::string name,std::string address){
    Customer customer(name,address);
    customerMap[customer.id] = customer;
    std::cout<<"Customer Successfully Added" << std::endl;
}

void processAccount::showcustomerDetails(int customerID){
    if (customerMap.count(customerID)> 0){
        Customer customer = customerMap[customerID];
        std::cout <<"Customer ID" << customer._id << std::endl;
        std::cout<<"Name: " << name

    }
}