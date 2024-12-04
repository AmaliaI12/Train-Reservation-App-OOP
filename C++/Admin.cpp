#include "Admin.hpp"
#include <regex>

// CONSTRUCTOR
Admin::Admin(vector<TrainTrip> *trips, unordered_map<string, string> *usrs,
             string k, string mail, string pswrd)
{
    trainTrips = trips;
    users = usrs;
    key = generateKey(k);
    adminEmail = mail;
    adminPassword = cipherText(adminPassword);
}

// TODO: upgrade valid date function with cases for months
// ADMIN OPERATIONS
bool isValidDate(int year, int month, int day)
{
    if (month < 1 || month > 12)
        return false;
    if (day < 1 || day > 31)
        return false;
    return true;
}

bool isValidCityName(const string &city)
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

void Admin::addTrip()
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
            throw invalid_argument("Invalid input for trip ID. Please enter an integer.");
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
        if (cin.fail() || !isValidDate(departureTime.year, departureTime.month, departureTime.day))
        {
            throw invalid_argument("Invalid departure date. Please enter a valid date.");
        }

        cout << "Enter arrival time (hour minute day month year): ";
        cin >> arrivalTime.hour >> arrivalTime.minute >> arrivalTime.day >> arrivalTime.month >> arrivalTime.year;
        if (cin.fail() || !isValidDate(arrivalTime.year, arrivalTime.month, arrivalTime.day))
        {
            throw invalid_argument("Invalid arrival date. Please enter a valid date.");
        }

        // TODO: Check if departure date is in the past

        cout << "Enter number of wagons: ";
        cin >> numOfWagons;
        if (numOfWagons <= 0)
        {
            throw invalid_argument("Number of wagons must be positive.");
        }

        TrainTrip newTrip(tripID, source.c_str(), destination.c_str(), departureTime, arrivalTime, numOfWagons);
        trainTrips->push_back(newTrip);
        cout << "Trip added successfully.\n";
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

int Admin::searchTrip()
{
    cout << "How do you want to search the trip you want to delete?\n";
    cout << "Options: [1] By route\t [2]By departure date\n";

    int searchMethod;
    cout << "Pick one (1/2): ";
    cin >> searchMethod;

    if (searchMethod != 1 && searchMethod != 2)
        return -1;

    if (searchMethod == 1)
    {
        string src, dest;
        cout << "Source: ";
        cin >> src;
        cout << "Destination: ";
        cin >> dest;

        for (int i = 0; i < (*trainTrips).size(); i++)
            if ((*trainTrips)[i].getSource() == src && (*trainTrips)[i].getDestination() == dest)
                (*trainTrips)[i].tripInfo();

        cout << "\n\nWhat trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

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
            aTime.day == arr.day && aTime.month == arr.month && aTime.year == arr.year)
            (*trainTrips)[i].tripInfo();
    }

    cout << "\n\nWhat trip do you want to delete? (insert the tripID or -1 if you want to abort): ";

    int deletedTripId;
    cin >> deletedTripId;
    return deletedTripId;
}

void Admin::deleteTrip(int tripID)
{
    int delID = searchTrip();

    if (delID == -1)
    {
        cout << "Delete aborted";
        return;
    }

    for (int i = 0; i < (*trainTrips).size(); i++)
    {
        if ((*trainTrips)[i].getTripID() == tripID)
        {
            trainTrips->erase(trainTrips->begin() + i);
            cout << "Trip with ID " << tripID << " has been successfully deleted.\n";
            return;
        }
    }
}

// CRYPTING PASSWORD METHODS
string Admin::generateKey(string str)
{
    string extendedKey = key;
    int x = str.size();

    for (size_t i = 0;; i++)
    {
        if (extendedKey.size() == x)
        {
            break;
        }
        extendedKey.push_back(key[i % key.size()]);
    }
    return extendedKey;
}

string Admin::cipherText(string str)
{
    string cipher_text;

    for (size_t i = 0; i < str.size(); i++)
    {
        char x = (str[i] + key[i]) % 256;
        cipher_text.push_back(x);
    }
    return cipher_text;
}

bool isValidEmail(string email)
{
    const regex emailPattern(R"(^[\w\.-]+@([\w-]+\.)+[\w-]{2,4}$)");

    return regex_match(email, emailPattern);
}

// ADMIN LOGIN
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

        if (email == adminEmail && adminPassword == cipherText(password))
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