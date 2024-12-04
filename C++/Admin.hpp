#ifndef ADMIN_H
#define ADMIN_H

#include "Trip.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>

class Admin{
private:
    std::vector<TrainTrip> *trainTrips;
    std::unordered_map<std::string, std::string> *users;
    std::string adminEmail;
    std::string adminPassword;
    std::string key;
public:
    //constructor
    Admin(std::vector<TrainTrip>* trips, std::unordered_map<std::string, std::string> *usrs, 
            std::string k, std::string mail, std::string pswrd);

    //crypting methods
    std::string generateKey(std::string str);
    std::string cipherText(std::string str);

    //admin login
    bool adminLogin();

    //admin operations
    void addTrip();
    int searchTrip();
    void deleteTrip(int tripID);
};

bool isValidDate(int year, int month, int day);
bool isValidCityName(const std::string& city);
bool isValidEmail(std::string email);

#endif
