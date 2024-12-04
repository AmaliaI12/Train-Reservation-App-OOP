#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

#include "User.hpp"
#include "Admin.hpp"
#include "Trip.hpp"

using namespace std;

// DataBasess
vector<TrainTrip> tripDatabase;
unordered_map<string, string> userDatabase;
string admEmail, admPswrd;

// import login information for users(email, password) from CSV file
void importUsers(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);
        string email, password;

        if (getline(ss, email, ',') && getline(ss, password))
        {
            // Add to the hashmap
            userDatabase[email] = password;
        }
        else
        {
            cerr << "Error: Incorrect line in file: " << line << '\n';
        }
    }

    file.close();
    cout << "Data imported successfully from " << filename << '\n';
}

// import train trips information
void importTrainTrips(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    string line;
    while (getline(file, line))
    {
        stringstream ss(line);

        int tripID, numOfWagons, emptySeats, firstClassEmptySeats;
        string destination, source;
        TIME departureTime, arrivalTime;

        string departureTimeStr, arrivalTimeStr;

        getline(ss, line, ',');
        tripID = stoi(line);

        getline(ss, source, ',');
        getline(ss, destination, ',');

        getline(ss, departureTimeStr, ',');
        stringstream departureStream(departureTimeStr);
        departureStream >> departureTime.year >> departureTime.month >> departureTime.day >> departureTime.hour >> departureTime.minute;

        getline(ss, arrivalTimeStr, ',');
        stringstream arrivalStream(arrivalTimeStr);
        arrivalStream >> arrivalTime.year >> arrivalTime.month >> arrivalTime.day >> arrivalTime.hour >> arrivalTime.minute;

        getline(ss, line, ',');
        numOfWagons = stoi(line);

        getline(ss, line, ',');
        emptySeats = stoi(line);

        getline(ss, line);
        firstClassEmptySeats = stoi(line);

        TrainTrip trip(tripID, source, destination, departureTime, arrivalTime, numOfWagons, emptySeats, firstClassEmptySeats);
        tripDatabase.push_back(trip);
    }

    file.close();
    cout << "Data imported successfully from " << filename << '\n';
}

// import admin login info
void importAdminLoginInfo(string filename)
{
    ifstream file(filename);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << '\n';
        return;
    }

    string line;
    getline(file, line);
    stringstream ss(line);
    string email, password;

    if (getline(ss, email, ',') && getline(ss, password))
    {
        admEmail = email;
        admPswrd = password;
    }
    else
    {
        cerr << "Error: Malformed line in file: " << line << '\n';
    }

    file.close();
    cout << "Data imported successfully from " << filename << '\n';
}


void updateTrainDataBase(string filename)
{
    ofstream file(filename, ios::trunc);

    if (!file.is_open())
    {
        cerr << "Error: Could not open file " << filename << " for writing.\n";
        return;
    }

    for (auto trip : tripDatabase)
    {
        TIME dep, arr;
        dep = trip.getDepartureTime();
        arr = trip.getArrivalTime();
        file << trip.getTripID() << ','
             << trip.getSource() << ','
             << trip.getDestination() << ','
             << dep.year << ' ' << dep.month << ' ' << dep.day << ' '
             << dep.hour << ' ' << dep.minute << ','
             << arr.year << ' ' << arr.month << ' ' << arr.day << ' '
             << arr.hour << ' ' << arr.minute << ','
             << trip.getNumOfWagons() << ',' << trip.getEmptySeats() <<
             ','<< trip.getFirstSeats() << '\n';
    }

    file.close();
    cout << "Data exported successfully to " << filename << '\n';
}

int main()
{
    // import data from CSV files
    importUsers(".\\dataBases\\userDatabase.csv");
    importTrainTrips(".\\dataBases\\trainTripsDataBase.csv");
    importAdminLoginInfo(".\\dataBases\\adminLoginInfo.csv");

    // the person is able to log out and log in again from another account
    char answer;
    do
    {
        cout << "How would you like to log in?\tAdmin [1] / User [2]: ";
        int userType;
        cin >> userType;
        getchar();

        if (userType != 1 && userType != 2)
        {
            char cont;
            do
            {
                cout << "Incorrect input. Do you wish to try again? (y/n): ";

                cin >> cont;
                if (cont == 'n' || cont == 'N')
                {
                    cout << "Goodbye!";
                    return 0;
                }

                int a;
                cout << "Please choose [1] or [2]: ";
                cin >> a;
                userType = a;
                if (userType == 1 || userType == 2)
                    cont = 'n';
            } while (cont == 'y' || cont == 'Y');
        }
        if (userType == 1)
        {
            cout << "----------- ADMIN LOGIN PAGE------------\n";
            Admin admin(&tripDatabase, &userDatabase, admEmail, admPswrd, ".\\dataBases\\trainTripsDataBase.csv");
            char c;
            do
            {
                bool loggedin = admin.adminLogin();
                if (loggedin == 1)
                    break;
                cout << "Do you want to try logging in again? y/n ";
                cin >> c;
                getchar();
                if (c == 'n' || c == 'N')
                {
                    cout << "Goodbye!";
                    return 0;
                }
            } while (c == 'y');

            char ans;
            do
            {
                int action;

                cout << "What would you like to do?\tAdd trip [1] / Delete trip [2]: ";
                cin >> action;

                if (action == 1)
                    admin.addTrip(".\\dataBases\\trainTripsDataBase.csv");
                if (action == 2)
                {
                    admin.deleteTrip();
                }
                cout << "Do you want to do something else? y/n: ";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
    
        }

        if (userType == 2)
        {
            cout << "----------- USER LOGIN PAGE------------\n";
            User user(&tripDatabase, &userDatabase, ".\\dataBases\\userDatabase.csv");

            cout << "Do you have an account? (y/n) ";
            char hasAccount;
            cin >> hasAccount;
            getchar();
            if (hasAccount == 'y')
            {
                char c;
                do
                {
                    bool loggedin = user.userLogin();
                    if (loggedin == 1)
                        break;
                    cout << "Do you want to try logging in again? (y/n): ";
                    cin >> c;
                    getchar();
                    if(c == 'n' || c == 'N')
                    {
                        cout << "Goodbye!";
                        return 0;
                    }
                } while (c == 'y');

                char ans;
                do
                {
                    int action;
                    cout << "What do you want to do?\tSearch Trip[1]/ Book seat on a trip[2]: ";
                    cin >> action;
                    if (action == 1)
                        user.searchTrip();
                    else if (action == 2)
                        user.bookTrip();

                    cout << "Do you want to do something else? y/n: ";
                    cin >> ans;
                } while (ans == 'y' || ans == 'Y');
            }
            else
            {
                user.userCreateAccount(".\\dataBases\\userDataBase.csv");
            }
        }

        updateTrainDataBase(".\\dataBases\\trainTripsDataBase.csv");
        importTrainTrips(".\\dataBases\\trainTripsDataBase.csv");
        cout << "You are now logged out. Do you want to log in again? y/n: ";
        cin >> answer;
        if (answer == 'n' || answer == 'N')
        {
            cout << "Goobye!";
            return 0;
        }

    } while (answer == 'y' || answer == 'Y');
    return 0;
}