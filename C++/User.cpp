#include "User.hpp"
#include "Admin.hpp"
#include <regex>
#include <fstream>

//CONSTRUCTOR
User::User(std::vector<TrainTrip>* trips, std::unordered_map<std::string, std::string> *usrs, 
            std::string k, std::string file){
    trainTrips = trips;
    users = usrs;
    key = k;
    filename = file;
}

//CYPTING PASSWORD METHODS
std::string User::generateKey(std::string str) {
    std::string extendedKey = key;
    int x = str.size();

    for (size_t i = 0;; i++) {
        if (extendedKey.size() == x) {
            break;
        }
        extendedKey.push_back(key[i % key.size()]);
    }
    return extendedKey;
}

std::string User::cipherText(std::string str) {
    std::string cipher_text;

    for (size_t i = 0; i < str.size(); i++) {
        char x = (str[i] + key[i]) % 256;
        cipher_text.push_back(x);
    }
    return cipher_text;
}

//USER LOGIN
bool User::userLogin() {
    std::string email;
    std::string password;
    try {
        std::cout << "Enter your email: ";
        std::getline(std::cin, email);
        std::cout << "Enter your password: ";
        std::getline(std::cin, password);

        if (!isValidEmail(email))
            throw std::invalid_argument("Invalid email");

        if ((*users).find(email) != (*users).end()) {
                if ((*users)[email] == cipherText(password)) {
                    std::cout << "Logged in successfully!\n";
                    return true;
                } else {
                    throw std::invalid_argument("Wrong password. Try again\n");
                }

        } else {
            throw std::invalid_argument("User does not exist");
        }
    } catch (const std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << "\n";
            return 0;
    }
    return 0;
}


std::string evaluatePasswordStrength(std::string password) {
    if (password.length() < 6) {
        throw std::invalid_argument("Password too short. Must be at least 6 characters.");
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

    for (char c : password) {
        if (std::islower(c)) hasLower = true;
        if (std::isupper(c)) hasUpper = true;
        if (std::isdigit(c)) hasDigit = true;
        if (std::ispunct(c)) hasSpecial = true;
    }

    if (!hasLower || !hasUpper || !hasDigit) {
        throw std::invalid_argument("Weak password. Include upper, lower case letters, and numbers.");
    }

    if (hasSpecial && password.length() >= 12) {
        return "good";
    } else if (password.length() >= 8) {
        return "ok";
    } else {
        return "weak";
    }
}


//USER CREATE ACCOUNT
void User::userCreateAccount(std::string filename){
    std::string email;
    std::string password, repeatedPassword;
    int t = 0;

    while (t == 0) {
        try {
            std::cout << "Enter your email: ";
            std::getline(std::cin, email);

            std::cout << "Enter your password: ";
            std::getline(std::cin, password);
            
            std::cout << "Enter your password again: ";
            std::getline(std::cin, repeatedPassword);

            if (!isValidEmail(email))
                throw std::invalid_argument("Invalid email");

            if  (password != repeatedPassword)
                throw std::invalid_argument("Passwords do not match.");

            std::string strength = evaluatePasswordStrength(password);

            if (strength == "weak") {
                throw std::invalid_argument("Password is weak. Please try again.");
            }

            std::cout << "Password strength: " << strength << "\n";
            
            //add account to database
            if ((*users).find(email) != (*users).end()) {
                std::cout << "Email already exists. Please use a different email.\n";
            } else {
                (*users)[email] = cipherText(password);
                // Append to CSV file
                std::ofstream file(filename, std::ios::app); // Open in append mode
                if (file.is_open()) {
                    file << email << "," << cipherText(password) << "\n";
                    file.close();
                    std::cout << "Account saved to file successfully.\n";
                } else {
                    std::cerr << "Error: Could not open file " << filename << " for appending.\n";
                }
                t = 1;
            }

        } catch (std::invalid_argument& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }
}

//USER ACTIONS
int User::searchTrip(){
    std::cout<<"How do you want to search the trip?\n";
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

        std::cout << "\n\nWhich trip do you want to reserve a seat for? (insert the tripID or -1 if you want to abort): ";

        int pickedTrip;
        std::cin >> pickedTrip;
        return pickedTrip;
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
            aTime.day == arr.day && aTime.month == arr.month && aTime.year == arr.year && 
            (*trainTrips)[i].emptySeats() > 0)
            (*trainTrips)[i].tripInfo();
    }

    std::cout << "\n\nWhich trip do you want to reserve a seat for? (insert the tripID or -1 if you want to abort): ";

    int pickedTrip;
    std::cin >> pickedTrip;
    return pickedTrip;
}

void User::bookTrip(){
    int tripId = searchTrip();
    int tripIndex;

    for (int i = 0 ; i < (*trainTrips).size(); i++) {
        if ((*trainTrips)[i].getTripID() == tripId) { 
            tripIndex = i;
            break;
        }
    }

    std::cout << "What type of seat do you want to book? (first class[1]/ second class[2]): ";
    int c;
    std::cin >> c;

    if (c == 1)
    {
        if ((*trainTrips)[tripIndex].firstClassEmptySeats() > 0) { 
            (*trainTrips)[tripIndex].addBookedSeat(c);
        }
    } else {
        if ((*trainTrips)[tripIndex].emptySeats() > 0) { 
            (*trainTrips)[tripIndex].addBookedSeat(c);
        }
    }
}
