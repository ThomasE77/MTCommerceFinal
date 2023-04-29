#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <ctime>
#include "Order.h"
#include "Cart.h"
#include "Product.h"
#include "User.h"
#include <chrono>


Order::Order(std::string user, std::string order, std::string date) {
        this->user = user;
        this->order = order;
        this->date = "";
    }
Order::Order(User user)
{
    this->user = user.getUsername();
    this->address = user.getAddress();
    this->payment = user.getPayment();
    this->date = getCurrentDateAsString();
}
std::string Order::getCurrentDateAsString() {
  // Get the current system time
  std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

  // Convert the system time to a time_t value
  std::time_t time = std::chrono::system_clock::to_time_t(now);

  // Convert the time_t value to a string
  std::string timeStr = std::ctime(&time);

  // Remove the trailing newline character from the string
  timeStr.pop_back();

  return timeStr;
}
  std::string Order::getHistory() {
    try {
      std::ifstream file("Orders.csv");
      std::string line;
      std::vector<std::string> orders;
      while (getline(file, line)) {
        std::istringstream iss(line);
        std::string user;
        std::string order;
        std::string date;
        if (getline(iss, user, ',') && getline(iss, order, ',') &&
            getline(iss, date, ',')) {
          if (user == this->user) {
            orders.push_back(line);
          }
        }
      }
      file.close();
      if (orders.size() > 0) {
        std::stringstream ss;
        for (auto &order : orders) {
          ss << order << std::endl;
        }
        return ss.str();
      } else {
        return "No orders found for user: " + this->user;
      }
    } catch (...) {
      return "Could not read order history.";
    }
  }
bool Order::removeUserOrders()
{
    ifstream inFile("Orders.csv");
    ofstream outFile("temp.csv");

    if (!inFile || !outFile)        
        return false;

    string line;
    bool userExisted = false;

    // Check if product ID exists in file
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string token;
        
        getline(iss, token, ','); // read username        
        if (token == this->user)
        {
                userExisted = true;
                continue; // skip writing the line with the matching product ID and username
        }
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (userExisted)
    {
        // Replace the original file with the new file
        remove("Orders.csv");
        rename("temp.csv", "Orders.csv");
        return true;
    } 
    else
    {
        remove("temp.csv");
        return false;
    }
}

  void Order::setUser(std::string user) { this->user = user; }

  void Order::setDate(std::string date) { this->date = date; }

  bool Order::readFile(std::string fileName) {
    try {
      std::ifstream file(fileName);
      std::string line;
      if (getline(file, line)) {
        std::istringstream iss(line);
        if (getline(iss, this->user, ',') && getline(iss, this->order, ',') &&
            getline(iss, this->date, ',')) {
          file.close();
          return true;
        }
      }
      file.close();
      return false;
    } catch (...) {
      return false;
    }
  }

  bool Order::writeFile() {
    try {
      std::ofstream file("Orders.csv");
      file << this->user << "," << this->date << "," << this->address << "," << this->payment
           << std::endl;
      file.close();
      return true;
    } catch (...) {
      return false;
    }
  }
