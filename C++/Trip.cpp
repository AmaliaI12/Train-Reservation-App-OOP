#include "Trip.hpp"

// Setters
void TrainTrip::setTripID(int id)
{
    tripID = id;
}

void TrainTrip::setDestination(string dest)
{
    destination = dest;
}

void TrainTrip::setSource(string src)
{
    source = src;
}

void TrainTrip::setTime(TIME departure, TIME arrival)
{
    departureTime = departure;
    arrivalTime = arrival;
}

void TrainTrip::setWagons(int numWags)
{
    if (numWags <= 0)
    {
        throw invalid_argument("Number of wagons must be positive.");
    }
    numOfWagons = numWags;
}

void TrainTrip::setEmpty(int empt, int fcempt)
{
    emptySeats = empt;
    firstClassEmptySeats = fcempt;
}

// Getters
int TrainTrip::getTripID()
{
    return tripID;
}

string TrainTrip::getDestination()
{
    return destination;
}

string TrainTrip::getSource()
{
    return source;
}

TIME TrainTrip::getDepartureTime()
{
    return departureTime;
}

TIME TrainTrip::getArrivalTime()
{
    return arrivalTime;
}

int TrainTrip::getNumOfWagons()
{
    return numOfWagons;
}

int TrainTrip::getEmptySeats()
{
    return emptySeats;
}

int TrainTrip::getFirstSeats()
{
    return firstClassEmptySeats;
}

// Constructor
TrainTrip::TrainTrip(int id, string src, string dest, TIME departure, TIME arrival, int wagons, int empt, int fcempt)
{
    setTripID(id);
    setSource(src);
    setDestination(dest);
    setTime(departure, arrival);
    setWagons(wagons);
    setEmpty(empt, fcempt);
}

void TrainTrip::addBookedSeat(int seatType)
{
    if (seatType == 1)
        firstClassEmptySeats--;
    else
        emptySeats--;
}

// Display Information
void TrainTrip::tripInfo()
{
    cout << "\n\n+++++++Trip Information++++++\n";
    cout << "Trip ID: " << tripID << "\n";
    cout << source << " --> " << destination << "\n";
    cout << "Departure Time: " << departureTime.hour << ":" << departureTime.minute << "\t"
         << departureTime.day << "/" << departureTime.month << "/" << departureTime.year << "\n";
    cout << "Arrival Time: " << arrivalTime.hour << ":" << arrivalTime.minute << "\t"
         << arrivalTime.day << "/" << arrivalTime.month << "/" << arrivalTime.year << "\n";
    cout << "Total Empty Seats: " << emptySeats << "\n";
    cout << "Total First Class Empty Seats: " << firstClassEmptySeats << "\n\n";
}
