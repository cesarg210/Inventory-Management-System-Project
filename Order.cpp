#include "Order.h"
#include <sstream>
#include <fstream>
#include <iostream>
using namespace std;

// Constructor
Order::Order(string orderID, string orderDate, string name, string status) {
    this->orderID = orderID;
    this->orderDate = orderDate;
    this->name = name;
    this->orderStatus = status;
}

// Deconstructor
Order::~Order(){
    for(auto order : orders) delete order;
    for(auto product : orderedProducts) delete product;
}

// Getters
string Order::getOrderID() const { return orderID; }
string Order::getOrderDate() const { return orderDate; }
string Order::getName() const { return name; }
string Order::getOrderStatus() const { return orderStatus; }

// Setters
void Order::setDeliveryDate(string date) { 
    this->deliveryDate = date;
}

void Order::setOrderStatus(string status) { 
    this->orderStatus = status; 
}

// Add product to orderedProducts vector
void Order::addProduct(Product* product) {
    orderedProducts.push_back(product);
}

// Remove product from orderedProducts vector
void Order::removeProduct(string productID) {

    for (auto it = orderedProducts.begin(); it != orderedProducts.end(); ++it) {

        if ((*it)->getProductID() == productID) {

            orderedProducts.erase(it);
            
            return;
        }
    }
}

// Returns products ordered
vector<Product*> Order::getOrderedProducts() const {

    return orderedProducts;

}
