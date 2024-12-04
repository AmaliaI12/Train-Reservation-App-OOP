#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

#include "User.hpp"
#include "Admin.hpp"
#include "Trip.hpp"

#define key "PHQAGILCX"

std::vector<TrainTrip> tripDatabase;
std::unordered_map<std::string, std::string> userDatabase;
std::string admEmail, admPswrd;

void importUsers(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string email, password;

        if (std::getline(ss, email, ',') && std::getline(ss, password)) {
            // Add to the hashmap
            userDatabase[email] = password;
        } else {
            std::cerr << "Error: Malformed line in file: " << line << '\n';
        }
    }

    file.close();
    std::cout << "Data imported successfully from " << filename << '\n';
}

void importTrainTrips(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);

        int tripID, numOfWagons;
        std::string destination, source;
        TIME departureTime, arrivalTime;

        std::string departureTimeStr, arrivalTimeStr;

        try {
            std::getline(ss, line, ',');
            tripID = std::stoi(line);

            std::getline(ss, source, ',');
            std::getline(ss, destination, ',');

            std::getline(ss, departureTimeStr, ',');
            std::stringstream departureStream(departureTimeStr);
            departureStream >> departureTime.year >> departureTime.month >> departureTime.day
                            >> departureTime.hour >> departureTime.minute;

            std::getline(ss, arrivalTimeStr, ',');
            std::stringstream arrivalStream(arrivalTimeStr);
            arrivalStream >> arrivalTime.year >> arrivalTime.month >> arrivalTime.day
                        >> arrivalTime.hour >> arrivalTime.minute;

            std::getline(ss, line, ',');
            numOfWagons = std::stoi(line);

            TrainTrip trip(tripID, source, destination, departureTime, arrivalTime, numOfWagons);
            tripDatabase.push_back(trip);

        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << "\n";
            std::cerr << e.what() << '\n';
            continue;
        }
    }

    file.close();
    std::cout << "Data imported successfully from " << filename << '\n';
}

void importAdminLoginInfo(std::string filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    std::string line;
    std::getline(file, line);
    std::stringstream ss(line);
    std::string email, password;

    if (std::getline(ss, email, ',') && std::getline(ss, password)) {
        admEmail = email;
        admPswrd = password;
    } else {
        std::cerr << "Error: Malformed line in file: " << line << '\n';
    }

    file.close();
    std::cout << "Data imported successfully from " << filename << '\n';
}

int main(){
    //import data from CSV files
    importUsers(".\\dataBases\\userDatabase.csv");
    importTrainTrips(".\\dataBases\\trainTripsDataBase.csv");
    importAdminLoginInfo(".\\dataBases\\adminLoginInfo.csv");

    std::cout << "How would you like to log in? [1]Admin/[2]User: ";
    int userType;
    std:: cin >> userType;

    if(userType == 1) {
        Admin admin(&tripDatabase, &userDatabase, key, admEmail, admPswrd);
        char c;
        do {
            bool loggedin = admin.adminLogin();
            if (loggedin == 1)
                break;
            std::cout << "Do you want to try logging in again? y/n ";
            std::cin >> c;
        } while (c == 'y');

        char ans;
        do{
            int action;
            std::cout << "What would you like to do? [1]Add trip/ [2]Delete trip: ";
            std::cin >> action;

            if( action == 1) {
                admin.addTrip();
            if (action == 2)
                std::cout << "Do you know the ID of the trip you want to delete? y/n: ";
                char r;
                std::cin >> r;

                int id;
                if ( r == 'n') 
                    id = admin.searchTrip();
                else
                    std::cin >> id;
                admin.deleteTrip(id);
            }
            std::cout << "Do you want to do something else? y/n";
                std::cin >> ans;
        }while(ans == 'y' || ans == 'Y');
    } else {
        User user(&tripDatabase, &userDatabase, key, ".\\dataBases\\userDatabase.csv");

        std::cout << "Do you have an account? (y/n) ";
        char hasAccount;
        std::cin >> hasAccount;
        getchar();
        if(hasAccount == 'y')
        {
            user.userLogin();
            
            char ans;
            do{
                int action;
                std::cout << "What do you want to do? Search Trip[1]/ Book seat on a trip[2]";
                std::cin >> action;
                if(action == 1)
                    user.searchTrip();
                if(action == 2)
                    user.bookTrip();
                
                std::cout << "Do you want to do something else? y/n";
                std::cin >> ans;
            }while(ans == 'y' || ans == 'Y');
        } else {
            user.userCreateAccount(".\\dataBases\\adminLoginInfo.csv");
        }
    }
    return 0;
}