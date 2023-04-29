#ifndef PRODUCT_H
#define PRODUCT_H

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

class Product {
private:
	int id;
	string name;
	string description;
	float price;
	int quantity;
	string category;

public:
    Product() {};
	Product(int id, string name, string description, float price, int quantity, string category);

	int getId() const;
	string getName();
	string getDescription();
	float getPrice();
	int getQuantity();
	string getCategory();
	void setId(int id);
	void setName(string name);
	void setDescription(string description);
	void setPrice(float price);
	void setQuantity(int quantity);
	void setCategory(string category);
	void viewItemsInCategory(string category);
	void readFile(vector<Product>& products);
	void writeFile(vector<Product>& products);
    void updateStock(int id, int quantity);

};

#endif // PRODUCT_H