#include "User.hpp"
#include "Admin.hpp"
#include <regex>
#include <fstream>

// constructor
User::User(vector<TrainTrip> *trips, unordered_map<string, string> *usrs, string file)
{
    trainTrips = trips;
    users = usrs;
    filename = file;
}

// user login
bool User::userLogin()
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

        if ((*users).find(email) != (*users).end())
        {
            if ((*users)[email] == cipherText(password, generateKey(password)))
            {
                cout << "Logged in successfully!\n";
                return true;
            }
            else
            {
                throw invalid_argument("Wrong password. Try again\n");
            }
        }
        else
        {
            throw invalid_argument("User does not exist");
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << "\n";
        return 0;
    }
    return 0;
}

string evaluatePasswordStrength(string password)
{
    if (password.length() < 6)
    {
        throw invalid_argument("Password too short. Must be at least 6 characters.");
    }

    bool hasLower = false, hasUpper = false, hasDigit = false, hasSpecial = false;

    for (char c : password)
    {
        if (islower(c))
            hasLower = true;
        if (isupper(c))
            hasUpper = true;
        if (isdigit(c))
            hasDigit = true;
        if (ispunct(c))
            hasSpecial = true;
    }

    if (!hasLower || !hasUpper || !hasDigit)
    {
        throw invalid_argument("Weak password. Include upper, lower case letters, and numbers.");
    }

    if (hasSpecial && password.length() >= 12)
    {
        return "good";
    }
    else if (password.length() >= 8)
    {
        return "ok";
    }
    else
    {
        return "weak";
    }
}

// user create account
void User::userCreateAccount(string filename)
{
    string email;
    string password, repeatedPassword;
    int t = 0;

    while (t == 0)
    {
        try
        {
            cout << "Enter your email: ";
            getline(cin, email);

            cout << "Enter your password: ";
            getline(cin, password);

            cout << "Enter your password again: ";
            getline(cin, repeatedPassword);

            if (!isValidEmail(email))
                throw invalid_argument("Invalid email");

            if (password != repeatedPassword)
                throw invalid_argument("Passwords do not match.");

            string strength = evaluatePasswordStrength(password);

            if (strength == "weak")
            {
                throw invalid_argument("Password is weak. Please try again.");
            }

            cout << "Password strength: " << strength << "\n";

            // add account to database
            if ((*users).find(email) != (*users).end())
            {
                cout << "Email already exists. Please use a different email.\n";
            }
            else
            {
                (*users)[email] = cipherText(password, generateKey(password));
                // Append to CSV file
                ofstream file(filename, ios::app); // Open in append mode
                if (file.is_open())
                {
                    file << email << "," << cipherText(password, generateKey(password)) << '\n';
                    file.close();
                    cout << "Account saved to file successfully.\n";
                }
                else
                {
                    cerr << "Error: Could not open file " << filename << " for appending.\n";
                }
                t = 1;
            }
        }
        catch (invalid_argument &e)
        {
            cerr << "Error: " << e.what() << "\n";
        }
    }
}

// user operations
void User::searchTrip()
{
    try
    {
        cout << "How do you want to search the trip?\n";
        cout << "Options: [1] By route\t [2]By departure date\n";

        int searchMethod;
        cout << "Pick one (1/2): ";
        cin >> searchMethod;

        if (searchMethod != 1 && searchMethod != 2)
        {
            cout << "Invalid input. Please try again\n";
            return;
        }
        if (searchMethod == 1)
        {
            string src, dest;
            cout << "Enter source city: ";
            cin.ignore();
            getline(cin, src);

            if (!isValidCityName(src))
            {
                throw invalid_argument("Source city name contains invalid characters.");
            }

            cout << "Enter destination city: ";
            getline(cin, dest);

            if (!isValidCityName(dest))
            {
                throw invalid_argument("Destination city name contains invalid characters.");
            }

            for (int i = 0; i < (*trainTrips).size(); i++)
                if ((*trainTrips)[i].getSource() == src && (*trainTrips)[i].getDestination() == dest)
                    (*trainTrips)[i].tripInfo();

            return;
        }

        cout << "Departure date: (dd mm yy): ";
        TIME dep;
        cin >> dep.day >> dep.month >> dep.year;

        if (cin.fail() || !isValidDate(dep.year, dep.month, dep.day))
        {
            throw invalid_argument("Invalid departure date. Please enter a valid date.");
        }

        cout << "Arrival date: (dd mm yy): ";
        TIME arr;
        cin >> arr.day >> arr.month >> arr.year;

        if (cin.fail() || !isValidDate(arr.year, arr.month, arr.day))
        {
            throw invalid_argument("Invalid arrival date. Please enter a valid date.");
        }

        for (int i = 0; i < (*trainTrips).size(); i++)
        {
            TIME dTime = (*trainTrips)[i].getDepartureTime();
            TIME aTime = (*trainTrips)[i].getArrivalTime();

            if (dTime.day == dep.day && dTime.month == dep.month && dTime.year == dep.year &&
                aTime.day == arr.day && aTime.month == arr.month && aTime.year == arr.year &&
                (*trainTrips)[i].getEmptySeats() > 0)
                (*trainTrips)[i].tripInfo();
        }
    }
    catch (const invalid_argument &e)
    {
        cerr << "Error: " << e.what() << endl;
    }
}

void User::bookTrip()
{
    char knowTripId;
    cout << "Do you know the id of the trip? y/n: ";
    cin >> knowTripId;

    int pickedTrip;

    if (knowTripId == 'n' || knowTripId == 'N')
        searchTrip();

    cout << "\n\nWhich trip do you want to reserve a seat for? (insert the tripID or -1 if you want to abort): ";

    cin >> pickedTrip;

    int tripIndex;

    for (int i = 0; i < (*trainTrips).size(); i++)
    {
        if ((*trainTrips)[i].getTripID() == pickedTrip)
        {
            tripIndex = i;
            break;
        }
    }

    cout << "What type of seat do you want to book? (first class[1]/ second class[2]): ";
    int c;
    cin >> c;

    if (c == 1)
    {
        if ((*trainTrips)[tripIndex].getFirstSeats() > 0)
        {
            (*trainTrips)[tripIndex].addBookedSeat(c);
        }
    }
    else
    {
        if ((*trainTrips)[tripIndex].getEmptySeats() > 0)
        {
            (*trainTrips)[tripIndex].addBookedSeat(c);
        }
    }
}
