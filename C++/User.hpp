#ifndef USER_H
#define USER_H

#include "Trip.hpp"
#include "Admin.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>

class User
{
private:
    vector<TrainTrip> *trainTrips;
    unordered_map<string, string> *users;
    string key;
    string filename;

public:
    // constructor
    User(vector<TrainTrip> *trips, unordered_map<string, string> *usrs,
         string key, string file);

    string generateKey(string str);
    string cipherText(string str);
    bool userLogin();
    void userCreateAccount(string filename);
    int searchTrip();
    void bookTrip();
};

#endif
