#include "Supplier.h"
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
using namespace std;

// Constructor
Supplier::Supplier(string name, string id, string contact) {
    supplierName = name;
    supplierID = id;
    contactInfo = contact;
}

// Getters
string Supplier::getSupplierName() const { return supplierName; }

string Supplier::getSupplierID() const { return supplierID; }

string Supplier::getContactInfo() const { return contactInfo; }

// Setters
void Supplier::setSupplierName(string name) { supplierName = name; }

void Supplier::setSupplierID(string id) { supplierID = id; }

void Supplier::setContactInfo(string contact) { contactInfo = contact; }
    

// Product management methods:

// Add product
void Supplier::addProduct(Product* product) {
    suppliedProducts.push_back(product);
}

// Remove product
void Supplier::removeProduct(string productID) {

    for (auto it = suppliedProducts.begin(); it != suppliedProducts.end(); ++it) {

        if ((*it)->getProductID() == productID) {

            suppliedProducts.erase(it);
            return; 
        }
    }
}

// Get supplied products
vector<Product*> Supplier::getSuppliedProducts() const {
    return suppliedProducts;
}
    