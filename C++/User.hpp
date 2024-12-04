#ifndef USER_H
#define USER_H

#include "Trip.hpp"
#include <iostream>
#include <cstring>
#include <vector>

class User{
private:
    std::vector<TrainTrip> *trainTrips;
    //TODO: add pointer to login data base (hashmap)
public:
    //constructor
    User(std::vector<TrainTrip>* trips);

    void userLogin();
    void userAutentificate();
    void searchTrip();
    void bookTrip();
};

#endif

