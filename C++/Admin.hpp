#ifndef ADMIN_H
#define ADMIN_H

#include "Trip.hpp"
#include <iostream>
#include <cstring>
#include <vector>
#include <unordered_map>
#include <fstream>


/*Realizez ca nu este deloc sigur sa pastrez aici cheia :(*/
#define  KEY "PHQAGILCX"
#define keySize 9

class Admin
{
private:
    std::vector<TrainTrip> *trainTrips;
    std::unordered_map<string, string> *users;
    string adminEmail;
    string adminPassword;
    string outFile;

public:
    // constructor
    Admin(std::vector<TrainTrip> *trips, std::unordered_map<string, string> *usrs,
          string mail, string pswrd, string out);

    // crypting methods

    // admin login
    bool adminLogin();

    // admin operations
    void addTrip(string outFile);
    int searchTrip();
    void deleteTrip();
};

string generateKey(string str);
string cipherText(string str, string extendedkey);
bool isValidDate(int year, int month, int day);
bool isValidCityName(string city);
bool isValidEmail(string email);

#endif
