#include "Admin.hpp"

Admin::Admin(std::vector<TrainTrip>* trips){
    trainTrips = trips;
}

//TODO: upgrade valid date function with cases for months
bool isValidDate(int year, int month, int day) {
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > 31) return false;
    return true;
}


bool isValidCityName(const std::string& city) {
    for (char c : city) {
        if (std::isalpha(c) == 0 && c != ' ') {
            return false;
        }
    }
    return true;
}

void Admin::addTrip() {
    int tripID;
    std::string source;
    std::string destination;
    TIME departureTime;
    TIME arrivalTime;
    int numOfWagons;

    try {

        std::cout << "Enter trip ID: ";
        std::cin >> tripID;
        if (std::cin.fail()) {
            throw std::invalid_argument("Invalid input for trip ID. Please enter an integer.");
        }

        std::cout << "Enter source city: ";
        std::cin.ignore();
        std::getline(std::cin, source);
        if (!isValidCityName(source)) {
            throw std::invalid_argument("Source city name contains invalid characters.");
        }

        std::cout << "Enter destination city: ";
        std::getline(std::cin, destination);
        if (!isValidCityName(destination)) {
            throw std::invalid_argument("Destination city name contains invalid characters.");
        }

        std::cout << "Enter departure time (hour minute day month year ): ";
        std::cin >> departureTime.hour >> departureTime.minute >> departureTime.day >> departureTime.month >> departureTime.year;
        if (std::cin.fail() || !isValidDate(departureTime.year, departureTime.month, departureTime.day)) {
            throw std::invalid_argument("Invalid departure date. Please enter a valid date.");
        }

        std::cout << "Enter arrival time (hour minute day month year): ";
        std::cin >> arrivalTime.hour >> arrivalTime.minute >> arrivalTime.day >> arrivalTime.month >> arrivalTime.year;
        if (std::cin.fail() || !isValidDate(arrivalTime.year, arrivalTime.month, arrivalTime.day)) {
            throw std::invalid_argument("Invalid arrival date. Please enter a valid date.");
        }

        //TODO: Check if departure date is in the past

        std::cout << "Enter number of wagons: ";
        std::cin >> numOfWagons;
        if (numOfWagons <= 0) {
            throw std::invalid_argument("Number of wagons must be positive.");
        }

        TrainTrip newTrip(tripID, source.c_str(), destination.c_str(), departureTime, arrivalTime, numOfWagons);
        trainTrips->push_back(newTrip);
        std::cout << "Trip added successfully.\n";

    } catch (const std::invalid_argument& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int Admin::searchTrip(){
    std::cout<<"How do you want to search the trip you want to delete?\n";
    std::cout<<"Options: [1] By route\t [2]By departure date\n";

    int searchMethod;
    std::cout<<"Pick one (1/2): ";
    std::cin>>searchMethod;

    if(searchMethod != 1 && searchMethod != 2)
        return -1;

    if (searchMethod == 1) {
        std::string src, dest;
        std::cout<<"Source: ";
        std::cin>>src;
        std::cout<<"Destination: ";
        std::cin>>dest;

        for (int i = 0 ; i < (*trainTrips).size(); i++)
            if ((*trainTrips)[i].getSource() == src && (*trainTrips)[i].getDestination() == dest)
                (*trainTrips)[i].tripInfo();

        std::cout << "\n\nWhat trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

        int deletedTripId;
        std::cin >> deletedTripId;
        return deletedTripId;
    } 

    std::cout << "Departure date: (dd mm yy): ";
    TIME dep;
    std::cin >> dep.day >> dep.month >> dep.year;

    std::cout << "Arrival date: (dd mm yy): ";
    TIME arr;
    std::cin >> arr.day >> arr.month >> arr.year;

    for (int i = 0 ; i < (*trainTrips).size(); i++) {
        TIME dTime = (*trainTrips)[i].getDepartureTime();
        TIME aTime = (*trainTrips)[i].getArrivalTime();

        if(dTime.day == dep.day && dTime.month == dep.month && dTime.year == dep.year &&
            aTime.day == arr.day && aTime.month == arr.month && aTime.year == arr.year)
            (*trainTrips)[i].tripInfo();
    }

    std::cout << "\n\nWhat trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

    int deletedTripId;
    std::cin >> deletedTripId;
    return deletedTripId;
}

void Admin::deleteTrip(int tripID) {
    int delID = searchTrip();

    if (delID == -1) {
        std::cout << "Delete aborted";
        return;
    }

    for (int i = 0 ; i < (*trainTrips).size() ; i++) {
        if ((*trainTrips)[i].getTripID() == tripID) {
            trainTrips->erase(trainTrips->begin() + i);
            std::cout << "Trip with ID " << tripID << " has been successfully deleted.\n";
            return;
    }
}

//TODO: admin login encripteaza parola si cauta in hashmap cu cheia username