#ifndef SUPPLIER_H
#define SUPPLIER_H
#include <vector>
#include "Product.h"
using namespace std;

class Supplier {

private:
    string supplierName;
    string supplierID;
    string contactInfo;
    vector<Product*> suppliedProducts;
    vector<Supplier*> suppliers;

public:
    // Constructor
    Supplier(string name, string id, string contact);
    
    // Getters
    string getSupplierName() const;
    string getSupplierID() const;
    string getContactInfo() const;
    
    // Setters
    void setSupplierName(string name);
    void setSupplierID(string id);
    void setContactInfo(string contact);

    // Product management
    void addProduct(Product* product);
    void removeProduct(string productID);
    vector<Product*> getSuppliedProducts() const;
};
#endif