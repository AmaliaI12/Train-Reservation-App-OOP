#include "Trip.hpp"

// Setters
void TrainTrip::setTripID(int id) {
    tripID = id;
}

void TrainTrip::setDestination(const std::string& dest) {
    destination = dest;
}

void TrainTrip::setSource(const std::string& src) {
    source = src;
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

// Getters
int TrainTrip::getTripID() const {
    return tripID;
}

std::string TrainTrip::getDestination() const {
    return destination;
}

std::string TrainTrip::getSource() const {
    return source;
}

TIME TrainTrip::getDepartureTime() const {
    return departureTime;
}

TIME TrainTrip::getArrivalTime() const {
    return arrivalTime;
}

int TrainTrip::getNumOfWagons() const {
    return numOfWagons;
}

std::vector<bool> TrainTrip::getTrainSeats() const {
    return trainSeats;
}

// Constructor
TrainTrip::TrainTrip(int id, const std::string& src, const std::string& dest, TIME departure, TIME arrival, int wagons) {
    setTripID(id);
    setSource(src);
    setDestination(dest);
    setTime(departure, arrival);
    setWagons(wagons);
    setTrainSeats();
}

int TrainTrip::emptySeats() const {
    int empty = 0;
    for (bool seat : trainSeats) {
        if (!seat) {
            empty++;
        }
    }
    return empty;
}

// Display Information
void TrainTrip::tripInfo() const {
    std::cout << "Trip Information:\n";
    std::cout << "Trip ID: " << tripID << "\n"; 
    std::cout << source << " --> " << destination << "\n";
    std::cout << "Departure Time: " << departureTime.hour << ":" << departureTime.minute << "\t"
              << departureTime.day << "/" << departureTime.month << "/" << departureTime.year << "\n";
    std::cout << "Arrival Time: " << arrivalTime.hour << ":" << arrivalTime.minute << "\t"
              << arrivalTime.day << "/" << arrivalTime.month << "/" << arrivalTime.year << "\n";
    std::cout << "Total Empty Seats: " << emptySeats() << "\n";
}
