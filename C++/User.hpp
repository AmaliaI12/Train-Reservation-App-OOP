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
    string filename;

public:
    // constructor
    User(vector<TrainTrip> *trips, unordered_map<string, string> *usrs, string file);

    //user login
    bool userLogin();

    //user create account
    void userCreateAccount(string filename);

    //user operations
    void searchTrip();
    void bookTrip();
};

#endif
