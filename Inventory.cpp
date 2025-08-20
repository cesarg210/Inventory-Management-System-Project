#include "Inventory.h"
#include <fstream>
#include <sstream>
#include <map>
#include <stdexcept>
#include <iostream>
#include <iomanip>
using namespace std;

// Constructor
Inventory::Inventory() {}

// Deconstructor
Inventory::~Inventory() {

    for (auto product : products) delete product;
    for (auto supplier : suppliers) delete supplier;
    for (auto order : orders) delete order;

}

    // Product management:

// Add product
void Inventory::addProduct(Product* product) {

    for(auto p : products) {

        if(p->getProductID() == product->getProductID()){

            throw runtime_error("Product ID already exists!");

        }

    }

    // Adds product and saves info to Products.csv and Products_Suppliers_map.csv
    products.push_back(product);
    saveProductInfo();
    saveProductSupplierMapping();

}

// Remove product
void Inventory::removeProduct(string productID) {

    for (auto it = products.begin(); it != products.end(); ++it) {

        // If product ID exists, delete and save info to csv files
        if ((*it)->getProductID() == productID) {

            delete *it;
            products.erase(it); 

            saveProductInfo();   
            saveProductSupplierMapping();
            return;

        }

    }
}

// Update product
void Inventory::updateProduct(string productID, Product* updatedProduct) {

    for (auto product : products) {

        if (product->getProductID() == productID) {

            *product = *updatedProduct;
            delete updatedProduct;
            return;

        }
    }
}

// Get all products
vector<Product*> Inventory::getProducts() const { return products; }

// Search product
Product* Inventory::searchProduct(string productID) {

    // searches for products, then returns product
    for (auto product : products) {

        if (product->getProductID() == productID) {
            return product;

        }
    }

    return nullptr;
}

// Overwrites product.csv dat
void Inventory::saveProductInfo(){

    // Clear existing content
    ofstream file("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Products.csv", ios::out | ios::trunc);
 
    if(!file.is_open()) {

        throw runtime_error("Unable to open Products.csv for writing");

    }

    // Header for file
    file << "ProductID,Name,Quantity,Price,Category\n";

    int i = 0;
    for(auto product : products) {

         // Writes new data to file  
        file << product->getProductID() << ","
             << product->getName() << ","
             << product->getQuantity() << ","
             << product->getPrice() << ","
             << product->getCategory();

        // Outputs newline until last product
        if(i < products.size() - 1) {

        file << endl;

        }
            ++i;
    }
}

    // Supplier management:

// Add supplier
void Inventory::addSupplier(Supplier* supplier) {

    for(auto s : suppliers) {

        if(s->getSupplierID() == supplier->getSupplierID()){

            throw runtime_error("Product ID already exists!");

        }

    }
    suppliers.push_back(supplier);
    saveSupplierInfo();
    saveProductSupplierMapping();

}

// Remove supplier
void Inventory::removeSupplier(string supplierID) {

    //Deletes supplier
    for (auto it = suppliers.begin(); it != suppliers.end(); ++it) {

        if ((*it)->getSupplierID() == supplierID) {
            delete *it;
            suppliers.erase(it);

            // Saves new data to files
            saveSupplierInfo();
            saveProductSupplierMapping();

            return;
        }

    }
    
   
}

// Search supplier
Supplier* Inventory::searchSupplier(string supplierID) {

    for (auto supplier : suppliers) {

        // If supplierID exists, return supplier
        if (supplier->getSupplierID() == supplierID) {

            return supplier;

        }

    }

    return nullptr;
}

vector<Supplier*> Inventory::getSuppliers() const { return suppliers; }

//Overwrites supplier.csv data
void Inventory::saveSupplierInfo() {

    // Clear existing content
    ofstream file("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Suppliers.csv", ios::out | ios::trunc); 

    if (!file.is_open()) {

        throw runtime_error("Unable to open Suppliers.csv for writing");

    }
    
    // Header for file
    file << "SupplierID,SupplierName,ContactInfo\n"; 
    
    // Writes new data to file
    for (size_t i = 0; i < suppliers.size(); ++i) { 

        file << suppliers[i]->getSupplierID() << ","
             << suppliers[i]->getSupplierName() << ","
             << suppliers[i]->getContactInfo();

        // Output newline until last supplier
        if (i < suppliers.size() - 1) {
            file << "\n";
        }

    }
    
    file.close();
}

//Overwrites Products_Suppliers_map.csv data
void Inventory::saveProductSupplierMapping() {

    // Clear existing content
    ofstream file("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Products_Suppliers_map.csv", ios::out | ios::trunc);

    if (!file.is_open()) {

        throw runtime_error("Unable to open Products_Suppliers_map.csv for writing");

    }

    // Header for file
    file << "ProductID,ProductName,SupplierID,SupplierName\n"; 

    bool firstLine = true;
    for (auto supplier : suppliers) {

        for (auto product : supplier->getSuppliedProducts()) {

            // Skips products removed by user
            if(product->getProductID().empty()){
                continue;
            }
            
            // Ensures no newline is added after last line
            if(!firstLine){
                file << endl;
             }
            
             // Writes new data to file
            file << product->getProductID() << ","
                 << product->getName() << ","
                 << supplier->getSupplierID() << ","
                 << supplier->getSupplierName();

            firstLine = false;     
              
        }

    }

    file.close();
}

    // Order management:

// PLace order
void Inventory::placeOrder(Order* order) {

    // Adds order, saves to Orders.csv
    orders.push_back(order);
    saveOrderDetails();

    // Update stock levels
    for (auto product : order->getOrderedProducts()) {

        // Checks if product exists
        Product* inventoryProduct = searchProduct(product->getProductID());
        if (inventoryProduct) {

            inventoryProduct->updateQuantity(-1); // Decrease by 1
            saveProductInfo();

        }
    }
}

// Update order status
void Inventory::updateOrderStatus(string orderID, string status) {

    for (auto order : orders) {

        // Updates order status with corresponding orderID parameter
        if (order->getOrderID() == orderID) {

            order->setOrderStatus(status);
            saveOrderDetails();

            return;
        }

    }
}

//Search orderID
Order* Inventory::searchOrder(string orderID){

    // If matching orderID is found, return that order
    for (auto order : orders) {

        if (order->getOrderID() == orderID) {
            return order;
        }

    }

    return nullptr;
}

    // Reports:

// Stock report
string Inventory::generateStockReport() const {

    stringstream ss;
    
    // Header to buffer
    ss << "Stock Report:\n";
    ss << setfill('-') << setw(50) << " " << "\n"
         << setfill(' ') << "\n";

     // Output product details for every product
    for (auto product : products) {

        ss << product->getProductDetails() << "\n";

    }

    return ss.str();
}

// Supplier reports
string Inventory::generateSupplierReport() const {

    stringstream ss;

    // Header to buffer
    ss << "Supplier Report:\n"; ss << endl;
    ss << setfill('-') << setw(50) << " " << "\n"
       << setfill(' ') << "\n";

    for (auto supplier : suppliers) {

        ss << "ID: " << supplier->getSupplierID() << endl;
        ss << "Name: " << supplier->getSupplierName() << endl;                                 
        ss << "Contact: " << supplier->getContactInfo() << endl;

        ss << "Products supplied:" << endl;

        vector<Product*> suppliedProducts = supplier->getSuppliedProducts();

        if (suppliedProducts.empty()) {

            ss << "  No products found.\n";
        } 
        else {
            // Outputs corresponding products to supplier
            for (auto product : suppliedProducts) {

                ss << product->getProductID() << ": " << product->getName() << endl;

            }
        }
        
        ss << endl;

    }
    // Output buffer
    return ss.str();
}

// Order reports
string Inventory::generateOrderReport() const {

    stringstream ss;

    // Header to buffer
    ss << "Order Report:\n";
    ss << setfill('-') << setw(50) << " " << "\n"
         << setfill(' ') << "\n";

    for (auto order : orders) {

        ss << "ID: " << order->getOrderID() << endl;
        ss << "Date: " << order->getOrderDate() << endl;
        ss << "Status: " << order->getOrderStatus() << endl;
        ss << endl;

    }

    return ss.str();
}


// Import / Export Products from csv files
void Inventory::importProductsFromCSV() {

    // Import supplier-product mappings
    map<string, string> productToSupplier;

    ifstream supplierFile("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Products_Suppliers_map.csv");
    string line;
    getline(supplierFile, line); // Skip header

    while (getline(supplierFile, line)) { 

        // Parse the lines
        stringstream ss(line);
        string productID, productName, supplierID, supplierName;

        getline(ss, productID, ',');
        getline(ss, productName, ',');
        getline(ss, supplierID, ',');
        getline(ss, supplierName);

        // Map product and supplier
        productToSupplier[productID] = supplierID;
        
    }
    supplierFile.close();



    // Import suppliers
    ifstream supplierData("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Suppliers.csv");
    getline(supplierData, line); // Skip header

    while (getline(supplierData, line)) {

        // Parse the lines
        stringstream ss(line);
        string supplierID, supplierName, contactInfo;

        getline(ss, supplierID, ',');
        getline(ss, supplierName, ',');
        getline(ss, contactInfo);

        // Add supplier
        addSupplier(new Supplier(supplierName, supplierID, contactInfo));
        
    }
    supplierData.close();



    // Import products and link to suppliers
    ifstream file("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Products.csv");
    getline(file, line); // Skip header

    while (getline(file, line)) {

        // Parse the lines
        stringstream ss(line);
        string productID, name, qtyStr, priceStr, category;

        getline(ss, productID, ',');
        getline(ss, name, ',');
        getline(ss, qtyStr, ',');
        getline(ss, priceStr, ',');
        getline(ss, category);

        try{ 
            // Add product 
            Product* product = new Product(name, productID, stoi(qtyStr), stod(priceStr), category);
            addProduct(product);
        
            // Link product to supplier
            if (productToSupplier.find(productID) != productToSupplier.end()) {

                string supplierID = productToSupplier[productID];

                for (auto supplier : suppliers) {

                    if (supplier->getSupplierID() == supplierID) {

                        supplier->addProduct(product);
                        break;
                    }
                }
            }
        }
        catch(const exception& e) {

            cout << "Error parsing product" << line << " - " << e.what() << endl;

        }
    }
    file.close();
}

void Inventory::exportProductsToCSV(string filename) {

    ofstream file(filename);
    
    // Header of Product.csv
    file << "ProductID, Name, Quantity, Price, Category\n";

    // Iterates through products, writes to file, outputs newline if not last line
    int i = 0;
    for (auto product : products) {

        file <<product->getProductID() << "," 
             << product->getName() << "," 
             << product->getQuantity() << "," 
             << product->getPrice() << "," 
             << product->getCategory();

        if(i < products.size() - 1){
            file << "\n";
        } 
        ++i;     
    }
    file.close();
}

// Import Order.csv
void Inventory::importOrderDetails() {

    ifstream orderData("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Orders.csv");

    if (!orderData.is_open()) {
        cout << "Error: Unable to open Orders.csv" << endl;
        return;
    }

    string line;
    getline(orderData, line); // Skip header

    while(getline(orderData, line)) {   

        // Parse lines
        stringstream ss(line);
        string orderID, date, name, status;

        getline(ss, orderID, ',');
        getline(ss, date, ',');
        getline(ss, name, ',');
        getline(ss, status, ',');

        // Add order
        orders.push_back(new Order(orderID, date, name, status));
        
    }
    orderData.close();
}

// Saves new order details to Orders.csv
void Inventory::saveOrderDetails(){

    // Overwrite file
    ofstream file("/Users/cesargallegos/.vscode/InventoryManagementCesarGall/Orders.csv", ios::out | ios::trunc); 

    if (!file.is_open()) {
        cout << "Error: Unable to open Orders.csv for writing" << endl;
        return;
    }
    // Write header to file
    file << "OrderID,OrderDate,ProductName,Status\n";

    // Write order details to file
    for (size_t i = 0; i < orders.size(); ++i) {   

        file << orders[i]->getOrderID() << ","
             << orders[i]->getOrderDate() << ","
             << orders[i]->getName() << ","
             << orders[i]->getOrderStatus();
        
         // Avoids newline after the last entry
        if (i < orders.size() - 1) {
            file << "\n";     
        }
    }

    file.close();
}

// Checks for low stock
vector<Product*> Inventory::checkLowStock() const {

    vector<Product*> lowStock;

    // Get product quantity and check if less than low stock threshold constant
    for (auto product : products) {

        if (product->getQuantity() < LOW_STOCK_THRESHOLD) {

            lowStock.push_back(product);

        }

    }

    return lowStock;
}