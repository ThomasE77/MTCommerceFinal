#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include "Product.h"
#include "Cart.h"

using namespace std;

    Product::Product(int id, string name, string description, float price, int quantity, string category) {
        this->id = id;
        this->name = name;
        this->description = description;
        this->price = price;
        this->quantity = quantity;
        this->category = category;
    }

    int Product::getId() const {
        return id;
    }

    string Product::getName() {
        return name;
    }

    string Product::getDescription() {
        return description;
    }

    float Product::getPrice() {
        return price;
    }

    int Product::getQuantity() {
        return quantity;
    }

    string Product::getCategory() {
        return category;
    }

    void Product::setId(int id) {
        this->id = id;
    }

    void Product::setName(string name) {
        this->name = name;
    }

    void Product::setDescription(string description) {
        this->description = description;
    }

    void Product::setPrice(float price) {
        this->price = price;
    }

    void Product::setQuantity(int quantity) {
        this->quantity = quantity;
    }

    void Product::setCategory(string category) {
        this->category = category;
    }

    void Product::viewItemsInCategory(string category) {
        ifstream inputFile("products.csv");
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            int id, quantity;
            string name, description, category2;
            float price;
            getline(ss, line, ',');
            id = stoi(line);
            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, line, ',');
            price = stof(line);
            getline(ss, line, ',');
            quantity = stoi(line);
            getline(ss, category2, ',');
            if (category2 == category) {
                cout << "ID: " << id << endl;
                cout << "Name: " << name << endl;
                cout << "Description: " << description << endl;
                cout << "Price: $" << price << endl;
                cout << "Quantity in Stock: " << quantity << endl;
                cout << "Category: " << category2 << endl << endl;
            }
        }
    }

    void Product::readFile(vector<Product>& products) {
        ifstream inputFile("products.csv");
        if (!inputFile.is_open()) {
          cout << "Failed to open file: products.csv" << endl;
          return;
        }
        string line;
        while (getline(inputFile, line)) {
            stringstream ss(line);
            int id, quantity;
            string name, description, category2;
            float price;
            getline(ss, line, ',');
            try {
              id = stoi(line);
              } catch (const invalid_argument& e)
            {
                cerr << "Invalid ID: " << line << endl;
                continue; // skip this line
            }
            getline(ss, name, ',');
            getline(ss, description, ',');
            getline(ss, line, ',');
            price = stof(line);
            getline(ss, line, ',');
            quantity = stoi(line);
            getline(ss, category2, ',');
            Product product(id, name, description, price, quantity, category2);
            products.push_back(product);
        }
    }

    void Product::writeFile(vector<Product>& products) {
        ofstream outputFile("products.csv");
        for (int i = 0; i < products.size(); i++) {
            outputFile << products[i].getId() << "," << products[i].getName() << "," << products[i].getDescription() << ","
                << products[i].getPrice() << "," << products[i].getQuantity() << "," << products[i].getCategory()
                << endl;
        }
    }

void Product::updateStock(int id, int quantity)
{
    cout << "here" << endl;
    ifstream inFile("products.csv");
    ofstream outFile("tempProduct.csv");

    if (!inFile || !outFile)
        return;
    
    string line;
    bool success = false;
    string name, description, category;
    float price;
    // Check if product ID exists in file
    while (getline(inFile, line))
    {
        istringstream iss(line);
        string token;

        getline(iss, token, ','); // read ID
        int stockId = stoi(token);
        if (stockId == id)
        {
            getline(iss, name, ',');
            getline(iss, description, ',');
            getline(iss, token, ',');
            price = stof(token);
            getline(iss, token, ','); //get quantity in stock product
            int stockQuantity = stoi(token);
            stockQuantity = stockQuantity - quantity;
            getline(iss, category, ',');
            success = true;
            outFile << stockId << "," 
                << name << "," 
                << description << "," 
                << price << "," 
                << stockQuantity << "," 
                << category << endl;
        }
        else
        {
            outFile << line << endl;
        }
    }
    inFile.close();
    outFile.close();

    // Replace the original file with the new file
    if (success)
    {
        remove("products.csv");
        rename("tempProduct.csv", "products.csv");
    }
    else
    {
        remove("tempProduct.csv");
    }
}
