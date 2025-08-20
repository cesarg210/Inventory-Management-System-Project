#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QTabWidget>
#include <QTableWidget>
#include <QHeaderView> 
#include <vector>
#include "Inventory.h"
#include "User.h"

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    std::vector<User> users;
    User* currentUser;
    Inventory inventory;

    QWidget* loginWidget;
    QLineEdit* usernameInput;
    QLineEdit* passwordInput;
    QPushButton* loginButton;

    QTabWidget* tabs;
    QTextEdit* outputDisplay;

    // Product Tab
    QLineEdit* prodIdInput;
    QLineEdit* prodNameInput;
    QLineEdit* prodQtyInput;
    QLineEdit* prodPriceInput;
    QLineEdit* prodCatInput;
    QPushButton* addProdButton;
    QPushButton* removeProdButton;
    QPushButton* searchProdButton;

    // Order Tab
    QLineEdit* orderIdInput;
    QLineEdit* orderDateInput;
    QLineEdit* orderProdIdInput;
    QLineEdit* orderStatusInput;
    QPushButton* placeOrderButton;

    // Stock Tab
    QLineEdit* stockIdInput;
    QLineEdit* stockQtyInput;
    QPushButton* updateStockButton;
    QTableWidget *inventoryTable;
    QPushButton *lowStockButton; 

    // Supplier Tab
    QLineEdit* suppIdInput;
    QLineEdit* suppNameInput;
    QLineEdit* suppContactInput;
    QPushButton* addSuppButton;
    QPushButton* removeSuppButton;

    // Report Tab
    QPushButton* stockReportButton;
    QPushButton* supplierReportButton;
    QPushButton* orderReportButton;

    void setupLoginScreen();
    void setupMainInterface();
    void updateDisplay(); 

private slots:
    void login();
    void addProduct();
    void searchProduct();
    void placeOrder();
    void updateStock();
    void checkLowStock();
    void removeProduct();
    void manageSuppliers();
    void generateReports();
    void removeSupplier();
};

#endif