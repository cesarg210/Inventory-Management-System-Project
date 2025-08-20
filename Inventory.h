#ifndef INVENTORY_H
#define INVENTORY_H
#include <vector>
#include <string>
#include <map>
#include "Product.h"
#include "Supplier.h"
#include "Order.h"
using namespace std;

class Inventory {
    
private:
    vector<Product*> products;
    vector<Supplier*> suppliers;
    vector<Order*> orders;
    const int LOW_STOCK_THRESHOLD = 50;

public:
    // Constructor
    Inventory();
    // Deconstructor
    ~Inventory();

    // Product management
    void addProduct(Product* product);
    void removeProduct(string productID);
    void updateProduct(string productID, Product* updatedProduct);
    vector<Product*> getProducts() const;
    void saveProductInfo();
    Product* searchProduct(string productID);

    // Supplier management
    void addSupplier(Supplier* supplier);
    void removeSupplier(string supplierID);
    void saveSupplierInfo();
    void saveProductSupplierMapping();
    Supplier* searchSupplier(string supplierID);
    vector<Supplier*> getSuppliers() const;
    

    // Order management
    void placeOrder(Order* order);
    void updateOrderStatus(string orderID, string status);
    void importOrderDetails();
    void saveOrderDetails();
    Order* searchOrder(string orderID);

    // Reporting
    string generateStockReport() const;
    string generateSupplierReport() const;
    string generateOrderReport() const;
    

    // Stock management
    void importProductsFromCSV();
    void exportProductsToCSV(string filename);
    vector<Product*> checkLowStock() const;
};
#endif