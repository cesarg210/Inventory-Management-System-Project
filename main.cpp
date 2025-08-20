#include "Product.h"
#include "Supplier.h"
#include "Inventory.h"
#include "Order.h"
#include "User.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <stdexcept>
#include <iomanip>
#include <fstream>

using namespace std;

// Initial login
int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}