#ifndef CART_H
#define CART_H

#include <string>
#include <vector>
#include "Product.h"
#include "User.h"

class Cart {
private:
    std::string user;
    std::vector<Product> products;
    std::vector<Product> productsA;
    float cost;
    int quantity;
public:
    Cart(std::string user);
    void addProduct(Product& product, int quantity);
    bool removeProduct(int id);
    float getTotalCost() const;
    std::string getUser() const;
    void setUser(std::string newUser);
    void getProducts();
    void clear();
    void writeFile(vector<Product>& products, int quantity);
    int getNumProducts() const;
    void readFile(vector<Product>& products);
    void setQuantity(int quantity);
    bool removeUserCart();
    void checkOut();
};

#endif