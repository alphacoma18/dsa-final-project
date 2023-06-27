#include <iostream>
#include <string>
#include <map>
#include <vector>

class BaseCustomer
{
protected:
    static int _id;
    std::string _name = "";
    std::string _address = "";
};

class Customer : public BaseCustomer
{
private:
    std::vector<int> _rentedVideos = {};

public:
    Customer(std::string name, std::string address);
    void rentVideo(int id);
    void returnVideo(int id);
};

class processAccount{
   private:
   std::map<int, Customer> customerMap;

   public:
    void addCustomer(std::string name, std::string address);
    void showcustomerDetails(int customerID);
    void printcustomerDetails();
}