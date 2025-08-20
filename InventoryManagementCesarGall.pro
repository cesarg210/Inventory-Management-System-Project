QT += core gui widgets charts
# Uncomment the next line if using charts for visualization
# QT += charts

TARGET = InventoryManagement
TEMPLATE = app

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    Inventory.cpp \
    Product.cpp \
    Supplier.cpp \
    Order.cpp \
    User.cpp

HEADERS += \
    mainwindow.h \
    Inventory.h \
    Product.h \
    Supplier.h \
    Order.h \
    User.h
