#include "mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QHeaderView> 
#include <QMessageBox>
#include <QTableWidget>
#include <fstream>
#include <sstream>
#include <iostream>

// Constructor
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Inventory Management System");
    setMinimumSize(1000, 600);
    
    // Usernames and passwords
    users.push_back(User("admin", "admin123", "admin"));
    users.push_back(User("manager", "manager123", "manager"));
    users.push_back(User("clerk", "clerk123", "clerk"));

    try
    {
        inventory.importProductsFromCSV();
        inventory.importOrderDetails();
    }
    catch (const exception &e)
    {
        QMessageBox::critical(this, "Error", "Failed to load CSV files: " + QString::fromStdString(e.what()));
    }

    setupLoginScreen();
}

// Deconstructor
MainWindow::~MainWindow() {}

// Login page
void MainWindow::setupLoginScreen()
{
    loginWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(loginWidget);

    layout->addWidget(new QLabel("Username:"));
    usernameInput = new QLineEdit(this);
    layout->addWidget(usernameInput);

    layout->addWidget(new QLabel("Password:"));
    passwordInput = new QLineEdit(this);
    passwordInput->setEchoMode(QLineEdit::Password);
    layout->addWidget(passwordInput);

    loginButton = new QPushButton("Login", this);
    layout->addWidget(loginButton);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::login);

    setCentralWidget(loginWidget);
}

// Main interface
void MainWindow::setupMainInterface()
{
    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    tabs = new QTabWidget(this);
    outputDisplay = new QTextEdit(this);
    outputDisplay->setReadOnly(true);

    // Product Tab
    QWidget *productTab = new QWidget();
    QVBoxLayout *prodLayout = new QVBoxLayout(productTab);
    prodLayout->addWidget(new QLabel("Product ID:"));
    prodIdInput = new QLineEdit();
    prodLayout->addWidget(prodIdInput);
    prodLayout->addWidget(new QLabel("Name:"));
    prodNameInput = new QLineEdit();
    prodLayout->addWidget(prodNameInput);
    prodLayout->addWidget(new QLabel("Quantity:"));
    prodQtyInput = new QLineEdit();
    prodLayout->addWidget(prodQtyInput);
    prodLayout->addWidget(new QLabel("Price:"));
    prodPriceInput = new QLineEdit();
    prodLayout->addWidget(prodPriceInput);
    prodLayout->addWidget(new QLabel("Category:"));
    prodCatInput = new QLineEdit();
    prodLayout->addWidget(prodCatInput);
    addProdButton = new QPushButton("Add Product");
    connect(addProdButton, &QPushButton::clicked, this, &MainWindow::addProduct);
    prodLayout->addWidget(addProdButton);
    removeProdButton = new QPushButton("Remove Product");
    connect(removeProdButton, &QPushButton::clicked, this, &MainWindow::removeProduct);
    prodLayout->addWidget(removeProdButton);
    searchProdButton = new QPushButton("Search Product");
    connect(searchProdButton, &QPushButton::clicked, this, &MainWindow::searchProduct);
    prodLayout->addWidget(searchProdButton);
    tabs->addTab(productTab, "Products");

    // Order Tab
    QWidget *orderTab = new QWidget();
    QVBoxLayout *orderLayout = new QVBoxLayout(orderTab);
    orderLayout->addWidget(new QLabel("Order ID (4 digits):"));
    orderIdInput = new QLineEdit();
    orderLayout->addWidget(orderIdInput);
    orderLayout->addWidget(new QLabel("Order Date (YYYY-MM-DD):"));
    orderDateInput = new QLineEdit();
    orderLayout->addWidget(orderDateInput);
    orderLayout->addWidget(new QLabel("Product ID:"));
    orderProdIdInput = new QLineEdit();
    orderLayout->addWidget(orderProdIdInput);
    orderLayout->addWidget(new QLabel("Status (Shipped/Delivered/Pending):"));
    orderStatusInput = new QLineEdit();
    orderLayout->addWidget(orderStatusInput);
    placeOrderButton = new QPushButton("Place Order");
    connect(placeOrderButton, &QPushButton::clicked, this, &MainWindow::placeOrder);
    orderLayout->addWidget(placeOrderButton);
    tabs->addTab(orderTab, "Orders");

    // Stock Tab
    QWidget *stockTab = new QWidget();
    QVBoxLayout *stockLayout = new QVBoxLayout(stockTab);
    stockLayout->addWidget(new QLabel("Product ID:"));
    stockIdInput = new QLineEdit();
    stockLayout->addWidget(stockIdInput);
    stockLayout->addWidget(new QLabel("Quantity Change (+/-):"));
    stockQtyInput = new QLineEdit();
    stockLayout->addWidget(stockQtyInput);
    updateStockButton = new QPushButton("Update Stock");
    connect(updateStockButton, &QPushButton::clicked, this, &MainWindow::updateStock);
    stockLayout->addWidget(updateStockButton);
    lowStockButton = new QPushButton("Check Low Stock");
    connect(lowStockButton, &QPushButton::clicked, this, &MainWindow::checkLowStock);
    stockLayout->addWidget(lowStockButton);
    tabs->addTab(stockTab, "Stock");


    // Supplier Tab
    QWidget *supplierTab = new QWidget();
    QVBoxLayout *suppLayout = new QVBoxLayout(supplierTab);
    suppLayout->addWidget(new QLabel("Supplier ID:"));
    suppIdInput = new QLineEdit();
    suppLayout->addWidget(suppIdInput);
    suppLayout->addWidget(new QLabel("Name:"));
    suppNameInput = new QLineEdit();
    suppLayout->addWidget(suppNameInput);
    suppLayout->addWidget(new QLabel("Contact Info:"));
    suppContactInput = new QLineEdit();
    suppLayout->addWidget(suppContactInput);
    addSuppButton = new QPushButton("Add Supplier");
    connect(addSuppButton, &QPushButton::clicked, this, &MainWindow::manageSuppliers);
    suppLayout->addWidget(addSuppButton);
    tabs->addTab(supplierTab, "Suppliers");
    removeSuppButton = new QPushButton("Remove Supplier");
    connect(removeSuppButton, &QPushButton::clicked, this, &MainWindow::removeSupplier);
    suppLayout->addWidget(removeSuppButton);

    // Report Tab
    QWidget *reportTab = new QWidget();
    QVBoxLayout *reportLayout = new QVBoxLayout(reportTab);
    stockReportButton = new QPushButton("Stock Report");
    connect(stockReportButton, &QPushButton::clicked, this, &MainWindow::generateReports);
    reportLayout->addWidget(stockReportButton);
    supplierReportButton = new QPushButton("Supplier Report");
    connect(supplierReportButton, &QPushButton::clicked, this, &MainWindow::generateReports);
    reportLayout->addWidget(supplierReportButton);
    orderReportButton = new QPushButton("Order Report");
    connect(orderReportButton, &QPushButton::clicked, this, &MainWindow::generateReports);
    reportLayout->addWidget(orderReportButton);
    tabs->addTab(reportTab, "Reports");

    mainLayout->addWidget(tabs);
    mainLayout->addWidget(outputDisplay);
    mainLayout->setStretch(1, 2);
    setCentralWidget(centralWidget);

    if (currentUser->getRole() == "clerk")
    {
        tabs->setTabEnabled(tabs->indexOf(stockTab), false);
        tabs->setTabEnabled(tabs->indexOf(supplierTab), false);
        addProdButton->setEnabled(false);  
        removeProdButton->setEnabled(false);
        updateStockButton->setEnabled(false);  
        lowStockButton->setEnabled(false);  
        addSuppButton->setEnabled(false);  
        removeSuppButton->setEnabled(false); 
    }
    if (currentUser->getRole() == "manager")
    {
        tabs->setTabEnabled(tabs->indexOf(supplierTab), false);
        addSuppButton->setEnabled(false);  
        removeSuppButton->setEnabled(false); 
    }

    outputDisplay->setText("Logged in as: " + QString::fromStdString(currentUser->getUsername()) +
                           " | Role: " + QString::fromStdString(currentUser->getRole()));
    updateDisplay();
}

// Reports tab
void MainWindow::generateReports()
{
    QPushButton *senderButton = qobject_cast<QPushButton *>(sender());
    if (senderButton == stockReportButton)
    {
        outputDisplay->setText(QString::fromStdString(inventory.generateStockReport()));
    }
    else if (senderButton == supplierReportButton)
    {
        outputDisplay->setText(QString::fromStdString(inventory.generateSupplierReport()));
    }
    else if (senderButton == orderReportButton)
    {
        outputDisplay->setText(QString::fromStdString(inventory.generateOrderReport()));
    }
}

// Low stock tab
void MainWindow::checkLowStock()
{
    vector<Product *> lowStockProducts = inventory.checkLowStock();

    if (lowStockProducts.empty())
    {
        QMessageBox::information(this, "Stock Check", "All products have sufficient stock.");
        return;
    }

    QString report = "⚠️ Low Stock Products ⚠️\n\n";
    for (auto product : lowStockProducts)
    {
        report += "Product: " + QString::fromStdString(product->getName()) + "\n";
        report += "Stock: " + QString::number(product->getQuantity()) + "\n";
        report += "Price: $" + QString::number(product->getPrice()) + "\n\n";
    }

    QMessageBox::warning(this, "Low Stock Alert", report);
}

// Login button
void MainWindow::login()
{
    string username = usernameInput->text().toStdString();
    string password = passwordInput->text().toStdString();

    for (auto &user : users)
    {
        if (user.getUsername() == username && user.authenticate(password))
        {
            currentUser = &user;
            setupMainInterface();
            return;
        }
    }
    QMessageBox::warning(this, "Login Failed", "Invalid username or password!");
}

// Add product tab
void MainWindow::addProduct()
{
    try
    {
        Product *product = new Product(
            prodNameInput->text().toStdString(),
            prodIdInput->text().toStdString(),
            prodQtyInput->text().toInt(),
            prodPriceInput->text().toDouble(),
            prodCatInput->text().toStdString());\
        // Add product and save    
        inventory.addProduct(product);
        inventory.saveProductInfo();
        inventory.saveProductSupplierMapping();
        outputDisplay->setText("Product added successfully!");
        prodNameInput->clear();
        prodIdInput->clear();
        prodQtyInput->clear();
        prodPriceInput->clear();
        prodCatInput->clear();
        updateDisplay();
    }
    catch (const exception &e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}

// Search product
void MainWindow::searchProduct()
{
    string productID = prodIdInput->text().toStdString();

    // checks if product exists
    Product *product = inventory.searchProduct(productID);
    if (product)
    {
        outputDisplay->setText(QString::fromStdString(product->getProductDetails()));
    }
    else
    {
        outputDisplay->setText("Product not found!");
    }
}

// Place order
void MainWindow::placeOrder()
{
    string orderId = orderIdInput->text().toStdString();
    string date = orderDateInput->text().toStdString();
    string prodId = orderProdIdInput->text().toStdString();
    string status = orderStatusInput->text().toStdString();

    Product *product = inventory.searchProduct(prodId);
    if (!product)
    {
        QMessageBox::warning(this, "Error", "Product not found!");
        return;
    }
    Order *order = new Order(orderId, date, product->getName(), status);
    // Adds order and saves
    order->addProduct(product);
    inventory.placeOrder(order);
    inventory.saveOrderDetails();
    inventory.saveProductInfo();
    outputDisplay->setText("Order placed successfully!");
    orderIdInput->clear();
    orderDateInput->clear();
    orderProdIdInput->clear();
    orderStatusInput->clear();
    updateDisplay();
}

// Update stock
void MainWindow::updateStock()
{
    string productID = stockIdInput->text().toStdString();
    int qty = stockQtyInput->text().toInt();
    Product *product = inventory.searchProduct(productID);
    if (product)
    {
        product->updateQuantity(qty);
        inventory.saveProductInfo();
        outputDisplay->setText("Stock updated successfully!");
        stockIdInput->clear();
        stockQtyInput->clear();
        updateDisplay();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Product not found!");
    }
}

// Remove product
void MainWindow::removeProduct()
{
    string productID = prodIdInput->text().toStdString();
    Product *product = inventory.searchProduct(productID);
    if (product)
    {
        inventory.removeProduct(productID);
        inventory.saveProductInfo();
        inventory.saveProductSupplierMapping();
        outputDisplay->setText("Product removed successfully!");
        prodIdInput->clear();
        updateDisplay();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Product not found!");
    }
}

//Manage suppliers
void MainWindow::manageSuppliers()
{
    try
    {
        Supplier *supplier = new Supplier(
            suppNameInput->text().toStdString(),
            suppIdInput->text().toStdString(),
            suppContactInput->text().toStdString());

        inventory.addSupplier(supplier);
        inventory.saveSupplierInfo();
        inventory.saveProductSupplierMapping();
        outputDisplay->setText("Supplier added successfully!");
        suppIdInput->clear();
        suppNameInput->clear();
        suppContactInput->clear();
        updateDisplay();
    }
    catch (const exception &e)
    {
        QMessageBox::warning(this, "Error", e.what());
    }
}

// Remove supplier
void MainWindow::removeSupplier()
{
    string supplierID = suppIdInput->text().toStdString();
    Supplier *supplier = inventory.searchSupplier(supplierID);
    if (supplier)
    {
        inventory.removeSupplier(supplierID);
        inventory.saveSupplierInfo();
        inventory.saveProductSupplierMapping();
        outputDisplay->setText("Supplier removed successfully!");
        suppIdInput->clear();
        updateDisplay();
    }
    else
    {
        QMessageBox::warning(this, "Error", "Supplier not found!");
    }
}

// Updates gui display
void MainWindow::updateDisplay()
{
    QString displayText = "Current Inventory:\n";
    displayText += "-------------------\n";
    for (const auto *product : inventory.getProducts())
    {
        displayText += QString::fromStdString(product->getProductDetails()) + "\n";
    }
    displayText += "\nSuppliers:\n";
    for (const auto *supplier : inventory.getSuppliers())
    {
        displayText += "ID: " + QString::fromStdString(supplier->getSupplierID()) +
                       ", Name: " + QString::fromStdString(supplier->getSupplierName()) +
                       ", Contact: " + QString::fromStdString(supplier->getContactInfo()) + "\n";
    }
    outputDisplay->setText(displayText);
}
