#include "Trip.hpp"

// Setters
void TrainTrip::setTripID(int id) {
    tripID = id;
}

void TrainTrip::setDestination(std::string dest) {
    destination = dest;
}

void TrainTrip::setSource(std::string src) {
    source = src;
}

void TrainTrip::setTime(TIME departure, TIME arrival) {
    departureTime = departure;
    arrivalTime = arrival;
}

void TrainTrip::setWagons(int numWags){
    if (numWags <= 0) {
        throw std::invalid_argument("Number of wagons must be positive.");
    }
    numOfWagons = numWags;
}

void TrainTrip::setTrainSeats(){
    if (numOfWagons <= 0) {
        throw std::logic_error("Number of wagons is not set or invalid.");
    }
    trainSeats.resize(numOfWagons * seatsInWagon, false);
}

// Getters
int TrainTrip::getTripID(){
    return tripID;
}

std::string TrainTrip::getDestination(){
    return destination;
}

std::string TrainTrip::getSource(){
    return source;
}

TIME TrainTrip::getDepartureTime(){
    return departureTime;
}

TIME TrainTrip::getArrivalTime(){
    return arrivalTime;
}

int TrainTrip::getNumOfWagons(){
    return numOfWagons;
}

std::vector<bool> TrainTrip::getTrainSeats(){
    return trainSeats;
}

// Constructor
TrainTrip::TrainTrip(int id, std::string src, std::string dest, TIME departure, TIME arrival, int wagons) {
    setTripID(id);
    setSource(src);
    setDestination(dest);
    setTime(departure, arrival);
    setWagons(wagons);
    setTrainSeats();
}

void TrainTrip::addBookedSeat(int seatType){
    int i = 0;
    if (seatType == 2) 
        i += seatsInWagon;
    for (; i < trainSeats.size() ; i++) {
        if(!trainSeats[i]){
            trainSeats[i] = 1;
            return;
        }
    }
}

int TrainTrip::emptySeats(){
    int empty = 0;
    for (int i = 0 ; i < seatsInWagon ; i++) {
        if (!trainSeats[i]) {
            empty++;
        }
    }
    return empty;
}

//there is only one first class wagon
int TrainTrip::firstClassEmptySeats(){
    int empty = 0;
    for (int i = 0 ; i < seatsInWagon ; i++) {
        if (!trainSeats[i]) {
            empty++;
        }
    }
    return empty;
}


// Display Information
void TrainTrip::tripInfo() {
    std::cout << "Trip Information:\n";
    std::cout << "Trip ID: " << tripID << "\n"; 
    std::cout << source << " --> " << destination << "\n";
    std::cout << "Departure Time: " << departureTime.hour << ":" << departureTime.minute << "\t"
              << departureTime.day << "/" << departureTime.month << "/" << departureTime.year << "\n";
    std::cout << "Arrival Time: " << arrivalTime.hour << ":" << arrivalTime.minute << "\t"
              << arrivalTime.day << "/" << arrivalTime.month << "/" << arrivalTime.year << "\n";
    std::cout << "Total Empty Seats: " << emptySeats() << "\n";
}
