#ifndef TRIP_h
#define TRIP_H

#include <iostream>
#include <cstring>
#include <vector>

#define seatsInWagon 100

typedef struct{
    int year;
    int month;
    int day;

    int hour;
    int minute;
}TIME;

class TrainTrip{
private:
    char destination[50];
    char source[50];
    TIME departureTime;
    TIME arrivalTime;
    int numOfWagons;
    std::vector<bool> trainSeats;
public:
    //setters
    void setDestination(char *dest);
    void setSource(char *src);
    void setTime(TIME departure, TIME arrival);
    void setWagons(int numWags);
    void setTrainSeats();

    //getters
    char *getDestination();
    char *getSource();
    TIME getDepartureTime();
    TIME getArrivalTime();
    int getNumOfWagons();
    std::vector<bool> getTrainSeats();

    int emptySeats();
    //display info
    void tripInfo();
};

#endif
