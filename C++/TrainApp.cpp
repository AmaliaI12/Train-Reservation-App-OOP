#include <iostream>
#include <unordered_map>
#include <fstream>
#include <string>
#include <sstream>

#include "User.hpp"
#include "Admin.hpp"
#include "Trip.hpp"

#define key "PHQAGILCX"
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

        int tripID, numOfWagons;
        string destination, source;
        TIME departureTime, arrivalTime;

        string departureTimeStr, arrivalTimeStr;

        try
        {
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

            TrainTrip trip(tripID, source, destination, departureTime, arrivalTime, numOfWagons);
            tripDatabase.push_back(trip);
        }
        catch (const exception &e)
        {
            cerr << "Error parsing line: " << line << "\n";
            cerr << e.what() << '\n';
            continue;
        }
    }

    file.close();
    cout << "Data imported successfully from " << filename << '\n';
}

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

int main()
{
    // import data from CSV files
    importUsers(".\\dataBases\\userDatabase.csv");
    importTrainTrips(".\\dataBases\\trainTripsDataBase.csv");
    importAdminLoginInfo(".\\dataBases\\adminLoginInfo.csv");

    cout << "How would you like to log in? [1]Admin/[2]User: ";
    int userType;
    cin >> userType;

    if (userType == 1)
    {
        Admin admin(&tripDatabase, &userDatabase, key, admEmail, admPswrd);
        char c;
        do
        {
            bool loggedin = admin.adminLogin();
            if (loggedin == 1)
                break;
            cout << "Do you want to try logging in again? y/n ";
            cin >> c;
        } while (c == 'y');

        char ans;
        do
        {
            int action;
            cout << "What would you like to do? [1]Add trip/ [2]Delete trip: ";
            cin >> action;

            if (action == 1)
            {
                admin.addTrip();
                if (action == 2)
                    cout << "Do you know the ID of the trip you want to delete? y/n: ";
                char r;
                cin >> r;

                int id;
                if (r == 'n')
                    id = admin.searchTrip();
                else
                    cin >> id;
                admin.deleteTrip(id);
            }
            cout << "Do you want to do something else? y/n";
            cin >> ans;
        } while (ans == 'y' || ans == 'Y');
    }
    else
    {
        User user(&tripDatabase, &userDatabase, key, ".\\dataBases\\userDatabase.csv");

        cout << "Do you have an account? (y/n) ";
        char hasAccount;
        cin >> hasAccount;
        getchar();
        if (hasAccount == 'y')
        {
            user.userLogin();

            char ans;
            do
            {
                int action;
                cout << "What do you want to do? Search Trip[1]/ Book seat on a trip[2]";
                cin >> action;
                if (action == 1)
                    user.searchTrip();
                if (action == 2)
                    user.bookTrip();

                cout << "Do you want to do something else? y/n";
                cin >> ans;
            } while (ans == 'y' || ans == 'Y');
        }
        else
        {
            user.userCreateAccount(".\\dataBases\\adminLoginInfo.csv");
        }
    }
    return 0;
}