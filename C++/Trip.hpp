#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define seatsInWagon 100

typedef struct
{
    int year;
    int month;
    int day;
    int hour;
    int minute;
} TIME;

class TrainTrip
{
private:
    int tripID;
    string destination;
    string source;
    TIME departureTime;
    TIME arrivalTime;
    int numOfWagons;
    vector<bool> trainSeats;

public:
    // Constructor
    TrainTrip(int id, string src, string dest, TIME departure, TIME arrival, int wagons);

    // Setters
    void setTripID(int id);
    void setDestination(string dest);
    void setSource(string src);
    void setTime(TIME departure, TIME arrival);
    void setWagons(int numWags);
    void setTrainSeats();

    // Getters
    int getTripID();
    string getDestination();
    string getSource();
    TIME getDepartureTime();
    TIME getArrivalTime();
    int getNumOfWagons();
    vector<bool> getTrainSeats();

    int emptySeats();
    void addBookedSeat(int classType);
    int firstClassEmptySeats();

    // Display info
    void tripInfo();
};

#endif