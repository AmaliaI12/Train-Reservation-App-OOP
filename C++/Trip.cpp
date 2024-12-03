#include "Trip.hpp"

//Setters
void TrainTrip::setDestination(char *dest) {
    std::strncpy(destination, dest, sizeof(destination) - 1);
    destination[sizeof(destination) - 1] = '\0';
}

void TrainTrip::setSource(char *src) {
    std::strncpy(source, src, sizeof(source) - 1);
    source[sizeof(source) - 1] = '\0'; 
}

void TrainTrip::setTime(TIME departure, TIME arrival) {
    departureTime = departure;
    arrivalTime = arrival;
}

void TrainTrip::setWagons(int numWags) {
    if (numWags <= 0) {
        throw std::invalid_argument("Number of wagons must be positive.");
    }
    numOfWagons = numWags;
}

void TrainTrip::setTrainSeats() {
    if (numOfWagons <= 0) {
        throw std::logic_error("Number of wagons is not set or invalid.");
    }
    trainSeats.resize(numOfWagons * seatsInWagon, false);
}

//Getters
char* TrainTrip::getDestination() {
    return destination;
}

char* TrainTrip::getSource() {
    return source;
}

TIME TrainTrip::getDepartureTime() {
    return departureTime;
}

TIME TrainTrip::getArrivalTime() {
    return arrivalTime;
}

int TrainTrip::getNumOfWagons() {
    return numOfWagons;
}

std::vector<bool> TrainTrip::getTrainSeats() {
    return trainSeats;
}

int TrainTrip::emptySeats(){
    int empty = 0;
    for (int i = 0; i < trainSeats.size(); i++)
        if (trainSeats[i] == 0)
            empty++;
    return empty;
}

// Display Information
void TrainTrip::tripInfo() {
    std::cout << "Trip Information:\n";
    std::cout << source << " -->  " << destination << "\n";
    std::cout << "Departure Time: " << departureTime.hour << ":" << departureTime.minute << "\t" << departureTime.day
              << "/" << departureTime.month << "/" << departureTime.year<< "\n";
    std::cout << "Arrival Time: " << arrivalTime.hour << ":" << arrivalTime.minute << "\t" << arrivalTime.day
              << "/" << arrivalTime.month << "/" << arrivalTime.year << "\n";
    std::cout << "Total Empty Seats: " << emptySeats() << "\n";
}