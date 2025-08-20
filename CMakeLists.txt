cmake_minimum_required(VERSION 3.10)
project(InventoryManagementCesarGall)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)  # Automatically handle Qt moc
set(CMAKE_AUTORCC ON)  # For resources, if needed later
set(CMAKE_AUTOUIC ON)  # For UI files, if added later

# QT6 path
set(Qt6_DIR "/opt/homebrew/Cellar/qt/6.8.2/lib/cmake/Qt6")
find_package(Qt6 COMPONENTS Widgets Charts REQUIRED)

# Add executable
add_executable(InventoryManagementCesarGall
    main.cpp
    mainwindow.cpp
    Inventory.cpp
    Product.cpp
    Supplier.cpp
    Order.cpp
    User.cpp
    mainwindow.h
    Inventory.h
    Product.h
    Supplier.h
    Order.h
    User.h
)
# Copy files to build directory
file(COPY ${CMAKE_SOURCE_DIR}/Orders.csv
          ${CMAKE_SOURCE_DIR}/Products.csv
          ${CMAKE_SOURCE_DIR}/Products_Suppliers_map.csv
          ${CMAKE_SOURCE_DIR}/Suppliers.csv
     DESTINATION ${CMAKE_BINARY_DIR})

target_link_libraries(InventoryManagementCesarGall Qt6::Widgets Qt6::Charts)