#ifndef USER_H
#define USER_H

#include "Trip.hpp"
#include "Admin.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>

class User{
private:
    std::vector<TrainTrip> *trainTrips;
    std::unordered_map<std::string, std::string> *users;
    std::string key;
    std::string filename;
public:
    //constructor
    User(std::vector<TrainTrip>* trips, std::unordered_map<std::string, std::string> *usrs, 
        std::string key, std::string file);

    std::string generateKey(std::string str);
    std::string cipherText(std::string str);
    bool userLogin();
    void userCreateAccount(std::string filename);
    int searchTrip();
    void bookTrip();
};

#endif

