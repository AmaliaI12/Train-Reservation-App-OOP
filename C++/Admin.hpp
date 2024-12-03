#ifndef ADMIN_H
#define ADMIN_H

#include "Trip.hpp"
#include <iostream>
#include <cstring>
#include <vector>

class Admin{
private:
    std::vector<TrainTrip> *trainTrips;
    //TODO: add pointer to login data base (hashmap)
public:
    //constructor
    Admin(std::vector<TrainTrip>* trips);

    void adminLogin();

    void addTrip(TrainTrip newTrip);
    int searchTrip();
    void deleteTrip(int tripID);
};

#endif
