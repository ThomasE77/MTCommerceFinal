#include "User.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

User::~User (){};

//writeFile function updates users.csv file with passed in values
bool User::writeFile(string username, string password, string firstName, string lastName, string address, string payment)
{
    ifstream inFile("users.csv");
    ofstream outFile("temp.csv");

    if(!inFile || !outFile)
        return false;
    
    string line;
    bool userFound = false;
    while(getline(inFile, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, ',');

        if(token == this->username)
        {
            outFile << username << "," << password << "," << firstName << "," << lastName << "," << address << "," << payment << endl;
            userFound = true;
            this->username = username;
            this->password = password;
            this->firstName = firstName;
            this->lastName = lastName;
            this->address = address;
            this->payment = payment;
            this->loggedIn = true;            
        }
        else
        {
            outFile << line << endl;
        }
    }
        inFile.close();
        outFile.close();
    
        if(!userFound)
            return false;

        remove("users.csv");
        rename("temp.csv", "users.csv");
    return true;
}
//createAccount function create an account with all the informations
bool User::createAccount(string username, string password, string firstName, string lastName, string address, string payment)
{
    ifstream inFile("users.csv");
    ofstream outFile("temp.csv", ios::app); // Open output file in append mode

    if (!inFile || !outFile)
        return false;

    string line;
    bool userExists = false;

    // Check if username already exists in file
    while (getline(inFile, line)) 
    {
        istringstream iss(line);
        string token;
        getline(iss, token, ',');
        if (token == username)
        {
            userExists = true;
        }
        else if (token > username && !userExists)
        {
            // Insert new user information in sorted order
            outFile << username << "," << password << "," << firstName << "," << lastName << "," << address << "," << payment << endl;
            userExists = true;
            this->username = username;
            this->password = password;
            this->firstName = firstName;
            this->lastName = lastName;
            this->address = address;
            this->payment = payment;
            this->loggedIn = true;
        }
        outFile << line << endl;
    }

    if(!userExists)
    {
        outFile << username << "," << password << "," << firstName << "," << lastName << "," << address << "," << payment << endl;
        this->username = username;
        this->password = password;
        this->firstName = firstName;
        this->lastName = lastName;
        this->address = address;
        this->payment = payment;
        this->loggedIn = true;
    }

    inFile.close();
    outFile.close();

    // Replace the original file with the new file
    remove("users.csv");
    rename("temp.csv", "users.csv");
    //adding userAccount fail
    if (!this->loggedIn)
    {
        return false;
    }
    //adding userAccount successful
    this->loggedIn = true;
    return true;
};
//delete account in the file that has current username
bool User::deleteAccount()
{
    ifstream inFile("users.csv");
    ofstream outFile("temp.csv");

    if (!inFile || !outFile)        
        return false;

    string line;
    bool userExists = false;

    // Check if username exists in file
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string token;
        getline(iss, token, ','); // read username
        if (token == this->username)
        {
            userExists = true;
            continue; // skip writing the line with the matching username
        }
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (userExists)
    {
        // Replace the original file with the new file
        remove("users.csv");
        rename("temp.csv", "users.csv");
        this->username = "";
        this->password = "";
        this->firstName = "";
        this->lastName = "";
        this->address = "";
        this->payment = "";
        this->loggedIn = false;
        return true;
    } 
    else
    {
        remove("temp.csv");
        return false;
    }
}
//login function compares username and password entered with values in the files
bool User::login(string username, string password)
{
    ifstream infile("users.csv");
    string line;

    if(!infile.is_open())
        return false;
    
    while(getline(infile, line))
    {
        vector<string> row;
        stringstream ss(line);
        string field;
        while(getline(ss, field, ','))
            row.push_back(field);

        if(row.size() == 6 && row[0] == username)
        {
            if(row[1] == password)    //username found
            {
                this->username = row[0];
                this->password = row[1];
                this->firstName = row[2];
                this->lastName = row[3];
                this->address = row[4];
                this->payment = row[5];
                infile.close();
                this->loggedIn = true;
                return true;
            }
            else
            {
                infile.close();
                return false;
            }
        }
    }
    infile.close();
    return false;
}
//set all value of the object to empty
bool User::logout()
{
    this->username = "";
    this->password = "";
    this->firstName = "";
    this->lastName = "";
    this->address = "";
    this->payment = "";
    this->loggedIn = false;
    return true;
};
//replace address with new address
bool User::setAddress(string newAddress)
{
    return writeFile(this->username, this->password, this->firstName, this->lastName, newAddress, this->payment);
};
//replace payment with new payment
bool User::setPayment(string newPayment)
{
    return writeFile(this->username, this->password, this->firstName, this->lastName, this->address, newPayment);
};
//return string of user's username
string User::getUsername()
{
    return this->username;
};
//return string of user's first name
string User::getFirstName()
{
    return this->firstName;
};
//return string of user's last name
string User::getLastName()
{
    return this->lastName;
};
//return string of user's address
string User::getAddress()
{
    return this->address;
};
//return string of user's payment method
string User::getPayment()
{
    return this->payment;
};
//return login status of the user
bool User::isLoggedIn()
{
    return this->loggedIn;
}