#include "Admin.hpp"
#include <regex>
#include <ctime>

// crypting methods
string generateKey(string str)
{
    string extendedKey = KEY;
    int x = str.size();
    for (size_t i = 0;; i++)
    {
        if (extendedKey.size() == x)
        {
            break;
        }
        extendedKey.push_back(KEY[i % keySize]);
    }
    return extendedKey;
}

string cipherText(string str, string extendedKey)
{
    string cipher_text;
    for (size_t i = 0; i < str.size(); i++)
    {
        char x = (str[i] + extendedKey[i]) % 256;
        cipher_text.push_back(x);
    }
    return cipher_text;
}

// constructor
Admin::Admin(vector<TrainTrip> *trips, unordered_map<string, string> *usrs,
             string mail, string pswrd, string file)
{
    trainTrips = trips;
    users = usrs;
    adminEmail = mail;
    adminPassword = pswrd;
    outFile = file;
}


// check functions
bool isValidDate(int year, int month, int day)
{
    if (month < 1 || month > 12)
        return false;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        if (day < 1 || day > 31)
            return false;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        if (day < 1 || day > 30)
            return false;
    }
    else if (month == 2)
    {
        if ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0)
        {
            if (day < 1 || day > 29)
                return false;
        }
        else
        {
            if (day < 1 || day > 28)
                return false;
        }
    }

    return true;
}

bool isValidCityName(string city)
{
    for (char c : city)
    {
        if (isalpha(c) == 0 && c != ' ')
        {
            return false;
        }
    }
    return true;
}

bool isFutureDate(TIME date) {
    time_t now = time(nullptr);
    tm *currentTime = localtime(&now);

    int currentYear = currentTime->tm_year + 1900;
    int currentMonth = currentTime->tm_mon + 1;
    int currentDay = currentTime->tm_mday;
    int currentHour = currentTime->tm_hour;
    int currentMinute = currentTime->tm_min;

    if (date.year > currentYear) {
        return true;
    } else if (date.year < currentYear) {
        return false;
    }

    if (date.month > currentMonth) {
        return true;
    } else if (date.month < currentMonth) {
        return false;
    }

    if (date.day > currentDay) {
        return true;
    } else if (date.day < currentDay) {
        return false;
    }

    if (date.hour > currentHour) {
        return true;
    } else if (date.hour < currentHour) {
        return false;
    }

    if (date.minute > currentMinute) {
        return true;
    } else {
        return false;
    }
}

bool isValidEmail(string email)
{
    const regex emailPattern(R"(^[\w\.-]+@([\w-]+\.)+[\w-]{2,4}$)");

    return regex_match(email, emailPattern);
}

// admin operations
void Admin::addTrip(string outFile)
{
    int tripID;
    string source;
    string destination;
    TIME departureTime;
    TIME arrivalTime;
    int numOfWagons;

    try
    {
        cout << "Enter trip ID: ";
        cin >> tripID;

        if (cin.fail())
        {
            throw invalid_argument("Invalid input for trip ID. ID must be an integer.");
        }

        cout << "Enter source city: ";
        cin.ignore();
        getline(cin, source);
        if (!isValidCityName(source))
        {
            throw invalid_argument("Source city name contains invalid characters.");
        }

        cout << "Enter destination city: ";
        getline(cin, destination);
        if (!isValidCityName(destination))
        {
            throw invalid_argument("Destination city name contains invalid characters.");
        }

        cout << "Enter departure time (hour minute day month year ): ";
        cin >> departureTime.hour >> departureTime.minute >> departureTime.day >> departureTime.month >> departureTime.year;
        if (cin.fail() || !isValidDate(departureTime.year, departureTime.month, departureTime.day) ||
            !isFutureDate(departureTime))
        {
            throw invalid_argument("Invalid departure date. Please enter a valid date.");
        }

        cout << "Enter arrival time (hour minute day month year): ";
        cin >> arrivalTime.hour >> arrivalTime.minute >> arrivalTime.day >> arrivalTime.month >> arrivalTime.year;
        if (cin.fail() || !isValidDate(arrivalTime.year, arrivalTime.month, arrivalTime.day) ||
            !isFutureDate(arrivalTime))
        {
            throw invalid_argument("Invalid arrival date. Please enter a valid date.");
        }

        cout << "Enter number of wagons: ";
        cin >> numOfWagons;
        if (numOfWagons <= 0)
        {
            throw invalid_argument("Number of wagons must be positive.");
        }

        int empt, fcempt;

        cout << "Enter number of empty seats: ";
        cin >> empt;
        if (empt < 0)
        {
            throw invalid_argument("Number of empty seats must be positive.");
        }

        cout << "Enter number of first class empty seats: ";
        cin >> fcempt;
        if (fcempt < 0)
        {
            throw invalid_argument("Number of first class empty seats must be positive.");
        }
        

        TrainTrip newTrip(tripID, source, destination, departureTime, arrivalTime, numOfWagons, empt, fcempt);
        trainTrips->push_back(newTrip);

        ofstream file(outFile, ios::app); 
        file << tripID << ","
                << source << ","
                << destination << ","
                << departureTime.year << " " << departureTime.month << " " << departureTime.day << " "
                << departureTime.hour << " " << departureTime.minute << ","
                << arrivalTime.year << " " << arrivalTime.month << " " << arrivalTime.day << " "
                << arrivalTime.hour << " " << arrivalTime.minute << ","
                << numOfWagons << "\n";
        file.close();
        cout << "Trip added successfully.\n";
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

int Admin::searchTrip()
{
    cout << "How do you want to search the trip?\n";
    cout << "Options: [1] By route\t [2]By departure date\n";

    int searchMethod;
    cout << "Pick one (1/2): ";
    cin >> searchMethod;

    if (searchMethod != 1 && searchMethod != 2)
    {   
        cout << "Invalid input. Please try again\n";
        return -1;
    }
    if (searchMethod == 1)
    {
        string src, dest;
        cout << "Enter source city: ";
        cin.ignore();
        getline(cin, src);
        cout << "Enter destination city: ";
        getline(cin, dest);

        for (int i = 0; i < (*trainTrips).size(); i++)
            if ((*trainTrips)[i].getSource() == src && (*trainTrips)[i].getDestination() == dest)
                (*trainTrips)[i].tripInfo();
        
        cout << "What trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

        int deletedTripId;
        cin >> deletedTripId;
        return deletedTripId;
    }

    cout << "Departure date: (dd mm yy): ";
    TIME dep;
    cin >> dep.day >> dep.month >> dep.year;

    cout << "Arrival date: (dd mm yy): ";
    TIME arr;
    cin >> arr.day >> arr.month >> arr.year;

    for (int i = 0; i < (*trainTrips).size(); i++)
    {
        TIME dTime = (*trainTrips)[i].getDepartureTime();
        TIME aTime = (*trainTrips)[i].getArrivalTime();

        if (dTime.day == dep.day && dTime.month == dep.month && dTime.year == dep.year &&
            aTime.day == arr.day && aTime.month == arr.month && aTime.year == arr.year &&
            (*trainTrips)[i].getEmptySeats() > 0)
            (*trainTrips)[i].tripInfo();
    }

    cout << "\n\nWhat trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

    int deletedTripId;
    cin >> deletedTripId;
    return deletedTripId;
}

void Admin::deleteTrip()
{
    int delID = searchTrip();

    if (delID == -1)
    {
        cout << "Delete aborted";
        return;
    }

    for (int i = 0; i < (*trainTrips).size(); i++)
    {
        if ((*trainTrips)[i].getTripID() == delID)
        {
            trainTrips->erase(trainTrips->begin() + i);
            cout << "Trip with ID " << delID << " has been successfully deleted.\n";
            return;
        }
    }
}

// admin login
bool Admin::adminLogin()
{
    string email;
    string password;
    try
    {
        cout << "Enter your email: ";
        getline(cin, email);
        cout << "Enter your password: ";
        getline(cin, password);

        if (!isValidEmail(email))
            throw invalid_argument("Invalid email");

        if (email == adminEmail && adminPassword == cipherText(password, generateKey(password)))
        {
            cout << "Logged in successfully!\n";
            return 1;
        }
        else
        {
            throw invalid_argument("Admin login information is not correct.\n");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 0;
    }
    return 0;
}