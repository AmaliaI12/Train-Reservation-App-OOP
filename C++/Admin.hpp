#ifndef ADMIN_H
#define ADMIN_H

#include "Trip.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>

class Admin
{
private:
    std::vector<TrainTrip> *trainTrips;
    std::unordered_map<string, string> *users;
    string adminEmail;
    string adminPassword;
    string key;

public:
    // constructor
    Admin(std::vector<TrainTrip> *trips, std::unordered_map<string, string> *usrs,
          string k, string mail, string pswrd);

    // crypting methods
    string generateKey(string str);
    string cipherText(string str);

    // admin login
    bool adminLogin();

    // admin operations
    void addTrip();
    int searchTrip();
    void deleteTrip(int tripID);
};

bool isValidDate(int year, int month, int day);
bool isValidCityName(const string &city);
bool isValidEmail(string email);

#endif
