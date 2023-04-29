#ifndef ORDER_H
#define ORDER_H

#include <string>
#include "User.h"

class Order {
public:
  Order(std::string user, std::string order, std::string date );
  Order(User user);
  std::string getHistory();
  void setUser(std::string user);
  void setDate(std::string date);
  bool readFile(std::string fileName);
  bool writeFile();
  bool removeUserOrders();
  string getCurrentDateAsString();

private:
  std::string user;
  std::string order;
  std::string date;
  std::string address;
  std::string payment;
};

#endif /* ORDER_H */
