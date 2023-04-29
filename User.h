#ifndef USER_H
#define USER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class User
{
private:
    string username;
    string password;
    string firstName;
    string lastName;
    string address;
    string payment;
    bool loggedIn;

    bool writeFile(string username, string password, string firstName, string lastName, string address, string payment);
    bool isUserExist(string username);
public:
    User() { this->loggedIn = false;};
    ~User();

    bool createAccount(string username, string password, string firstName, string lastName, string address, string payment);
    bool deleteAccount();

    bool login(string username, string password);
    bool logout();

    bool setAddress(string newAddress);
    bool setPayment(string newPayment);

    string getUsername();
    string getFirstName();
    string getLastName();
    string getAddress();
    string getPayment();

    bool isLoggedIn();
};

#endif