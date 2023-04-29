#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Cart.h"
#include "Product.h"
#include <algorithm>
#include <functional>
#include "Order.h"
#include "User.h"

using namespace std;

    Cart::Cart(std::string user)
    {
        this->user = user;
        this->cost = 0.0f;
        //this->pCounter = 0;
    }
    // Add a product to the cart
    void Cart::addProduct(Product& product, int quantity) {
        cout << "Testing Add Product" << endl;
        //product.setQuantity(quantity);
        products.push_back(std::ref(product));
        productsA.push_back(std::ref(product));
        cost += product.getPrice() * quantity;
        Cart::writeFile(products, quantity);
        //product.writeFile(products);
        products.clear();
        //pCounter = pCounter + 1;
    }

bool Cart::removeProduct(int id)
{
    ifstream inFile("Cart.csv");
    ofstream outFile("temp.csv");

    if (!inFile || !outFile)        
        return false;

    string line;
    bool productExists = false;

    // Check if product ID exists in file
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string token;
        
        getline(iss, token, ','); // read username        
        if (token == this->user)
        {
            getline(iss, token, ','); // read product ID
            int productID = stoi(token);
            if(productID == id)
            {
                productExists = true;
                continue; // skip writing the line with the matching product ID and username
            }
        }
        outFile << line << endl;
    }

    inFile.close();
    outFile.close();

    if (productExists)
    {
        // Replace the original file with the new file
        remove("Cart.csv");
        rename("temp.csv", "Cart.csv");
        return true;
    } 
    else
    {
        remove("temp.csv");
        return false;
    }
}

    void Cart::setQuantity(int quantity) {
      this->quantity = quantity;
    }
    bool removeProduct(Product& product, int quantity) {
      
    }
    // Get the total cost of the cart
    float Cart::getTotalCost() const {
        return cost;
    }

    // Get the user associated with the cart
    std::string Cart::getUser() const {
        return user;
    }

    // Set the user associated with the cart
    void Cart::setUser(std::string newUser) {
        user = newUser;
    }

    // Get the vector of products in the cart
  /*  std::vector<Product> Cart::getProducts() const {
        return products;
    }
  */
bool Cart::removeUserCart()
{
    ifstream inFile("Cart.csv");
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
        remove("Cart.csv");
        rename("temp.csv", "Cart.csv");
        return true;
    } 
    else
    {
        remove("temp.csv");
        return false;
    }
}
    void Cart::getProducts() {
        ifstream inputFile("Cart.csv");
        string line;
        this->cost = 0;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            int id, quantity;
            string name, description, category2;
            float price;
            getline(ss, line, ',');
            string user = line;
          if (user == this->user){
            getline(ss, line, ',');
            id = stoi(line);
            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, line, ',');
            price = stof(line);
            getline(ss, line, ',');
            quantity = stoi(line);
            getline(ss, category2, ',');
            cout << "ID: " << id << endl;
            cout << "Name: " << name << endl;
            cout << "Description: " << description << endl;
            cout << "Price: $" << price << endl;
            cout << "Quantity in Stock: " << quantity << endl;
            cout << "Category: " << category2 << endl << endl;
            this->cost += price;
          }
        }
    }

    int Cart::getNumProducts() const {
      return products.size();
    }

    // Remove all products from the cart
    void Cart::clear() {
        ifstream inputFile("Cart.csv");
        ofstream tempFile("temp.csv");
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            string user;
            getline(ss, user, ',');
            if (user != this->user) {
                // Keep the product associated with other users
                tempFile << line << endl;
            }
        }
        inputFile.close();
        tempFile.close();
    
        // Delete the original Cart.csv file and rename the temporary file
        remove("Cart.csv");
        rename("temp.csv", "Cart.csv");
    
        // Clear the products vector and reset the cost
        products.clear();
        cost = 0.0f;
    }
    
    void Cart::writeFile(vector<Product>& products, int quantity) {
        ofstream outputFile("Cart.csv", std::ios::app);
        
        for (int i = 0; i < products.size(); i++) {
            products[i].setQuantity(quantity);
            outputFile << user << ","
                << products[i].getId() << "," 
                << products[i].getName() << "," 
                << products[i].getDescription() << ","
                << products[i].getPrice() << "," 
                << quantity << ","
                << products[i].getCategory()
                << endl;
        }
    }


void Cart::checkOut() 
{
    for(int i = 0; i < productsA.size(); i++)
    {
        cout << "inside loop" << endl;
        productsA[i].updateStock(productsA[i].getId(), productsA[i].getQuantity());
    }

    // Update the cart file
    clear();
      
}







