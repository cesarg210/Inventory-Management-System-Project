#ifndef ORDER_H
#define ORDER_H
#include <string>
#include <vector>
#include "Product.h"
using namespace std;

class Order {

private:
    string orderID;
    vector<Order*> orders;
    vector<Product*> orderedProducts;
    string orderDate;
    string deliveryDate;
    string orderStatus;
    string name;
    string status;

public:
    // Constructor
    Order(string orderID, string orderDate, string name, string status);
    // Deconstrucor
    ~Order();

    // Getters
    string getOrderID() const;
    string getOrderDate() const;
    string getName() const;
    string getOrderStatus() const;
    
    // Setters
    void setDeliveryDate(string date);
    void setOrderStatus(string status);

    // Product management
    void addProduct(Product* product);
    void removeProduct(string productID);
    vector<Product*> getOrderedProducts() const;
};
#endif