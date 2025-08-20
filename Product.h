#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;

class Product {

private:
    string name;
    string productID;
    int quantity;
    double price;
    string category;

public:
    // Constructor
    Product(string name, string productID, int quantity, 
            double price, string category);
    
    // Getters
    string getName() const;
    string getProductID() const;
    int getQuantity() const;
    double getPrice() const;
    string getCategory() const;

    // Setters
    void setName(string name);
    void setProductID(string productID);
    void setQuantity(int quantity);
    void setPrice(double price);
    void setCategory(string category);

    // Additional methods
    void updateQuantity(int amount);
    string getProductDetails() const;
};
#endif