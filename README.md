# Inventory Management System

## Description
This Inventory Management System is a C++ application with a Qt-based GUI that allows users to manage products, suppliers, and orders efficiently. The system supports adding, updating, and deleting products and suppliers, placing orders, and generating reports. It incorporates file handling for data persistence and role-based access control.

## Features
- **User Authentication:** Login system with different roles (Admin, Manager, Clerk).
- **Product Management:** Add, remove, search, and update product details.
- **Supplier Management:** Add, remove, and link suppliers to products.
- **Order Management:** Place orders, update order status, and track orders.
- **Reports:** Generate stock, supplier, and order reports.
- **Low Stock Alerts:** Notifies users when inventory is running low.
- **CSV File Handling:** Stores and retrieves data from CSV files.

## Installation
### Prerequisites
- **Qt Framework** (Qt Creator or Qt5 installed)
- **C++ Compiler** (g++, MSVC, or Clang)
- **CMake** (optional but recommended)

### Steps

1. Navigate to the build directory, clean previous builds, generate Makefile, compile:
   ```sh
   cd /Users/cesargallegos/.vscode/InventoryManagementCesarGall/build
   make clean
   qmake ..
   make
   ```
2. Run the executable:
   ```sh
   ./InventoryManagement.app/Contents/MacOS/InventoryManagement
   ```

## Usage
1. **Launch the Application**
2. **Login as an Admin, Manager, or Clerk** (default users):
   - Admin: `admin / admin123`
   - Manager: `manager / manager123`
   - Clerk: `clerk / clerk123`
3. **Navigate through tabs**:
   - Products: Add, remove, search, update products.
   - Orders: Place and manage orders.
   - Suppliers: Manage suppliers and their products.
   - Reports: View stock, supplier, and order reports.
4. **Logout when done.**

## File Structure
```
📂 InventoryManagement
 ├── 📂 src
 │   ├── main.cpp
 │   ├── mainwindow.cpp
 │   ├── Inventory.cpp
 │   ├── Order.cpp
 │   ├── Product.cpp
 │   ├── Supplier.cpp
 │   ├── User.cpp
 ├── 📂 include
 │   ├── mainwindow.h
 │   ├── Inventory.h
 │   ├── Order.h
 │   ├── Product.h
 │   ├── Supplier.h
 │   ├── User.h
 ├── 📂 data
 │   ├── Products.csv
 │   ├── Suppliers.csv
 │   ├── Products_Suppliers_map.csv
 ├── README.md
 ├── InventoryManagement.pro (Qt Project File)
```

## Future Enhancements
- Switch from CSV to an SQL database for better data handling.
- Improve security with encrypted passwords.
- Enhance UI with a modernized design.

## Contributors
- **[Cesar Gallegos]** - Developer