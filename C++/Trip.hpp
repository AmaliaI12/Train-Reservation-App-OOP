#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <string>
#include <vector>

#define seatsInWagon 100

typedef struct {
    int year;
    int month;
    int day;
    int hour;
    int minute;
} TIME;

class TrainTrip {
private:
    int tripID;
    std::string destination;
    std::string source;
    TIME departureTime;
    TIME arrivalTime;
    int numOfWagons;
    std::vector<bool> trainSeats;

public:
    // Constructor
    TrainTrip(int id, std::string src, std::string dest, TIME departure, TIME arrival, int wagons);

    // Setters
    void setTripID(int id);
    void setDestination(std::string dest);
    void setSource(std::string src);
    void setTime(TIME departure, TIME arrival);
    void setWagons(int numWags);
    void setTrainSeats();

    // Getters
    int getTripID();
    std::string getDestination();
    std::string getSource();
    TIME getDepartureTime();
    TIME getArrivalTime();
    int getNumOfWagons();
    std::vector<bool> getTrainSeats();

    int emptySeats();
    void addBookedSeat(int classType);
    int firstClassEmptySeats();

    // Display info
    void tripInfo();
};

#endif