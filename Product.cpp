#include "Product.h"
#include <sstream>
#include <iomanip>
#include <iostream>
using namespace std;

// Constructor
Product::Product(string name, string productID, int quantity, 
                 double price, string category) {
    this->name = name;
    this->productID = productID;
    this->quantity = quantity;
    this->price = price;
    this->category = category;
}

// Getters
string Product::getName() const { return name; }
string Product::getProductID() const { return productID; }
int Product::getQuantity() const { return quantity; }
double Product::getPrice() const { return price; }
string Product::getCategory() const { return category; }
string Product::getProductDetails() const {
    
    stringstream ss;
    ss << "ID:\t" << productID << endl;
    ss << "Name:\t" << name << endl;
    ss << "Quantity:\t" << quantity << endl;
    ss << "Price:\t$" << price << endl;
    ss << endl;

    return ss.str();
}

// Setters
void Product::setName(string name) { this->name = name; }
void Product::setProductID(string productID) { this->productID = productID; }
void Product::setQuantity(int quantity) { this->quantity = quantity; }
void Product::setPrice(double price) { this->price = price; }
void Product::setCategory(string category) { this->category = category; }

// Quantity update
void Product::updateQuantity(int amount) {
    quantity += amount;
}