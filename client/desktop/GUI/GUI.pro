QT       += core gui network websockets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    src/screens/Menu/menu.cpp  \   
    src/screens/Orders/orders.cpp \
    src/screens/Ingredients/ingredients.cpp \
    src/screens/Calculator/calculator.cpp \
    src/screens/Clients/clients.cpp \

HEADERS += \
    mainwindow.h \
    defines/enums/MenuItems.hpp \
    src/screens/Menu/menu.h \ 
    src/screens/Orders/orders.h \
    src/screens/Ingredients/ingredients.h \
    src/screens/Calculator/calculator.h \
    src/screens/Clients/clients.h \

FORMS += \
    ui/mainwindow.ui \
    ui/menu.ui \
    ui/orders.ui \
    ui/ingredients.ui \
    ui/calculator.ui \
    ui/clients.ui

LIBS += -L/../build -app \
    -lQt5Network \
    -lQt5WebSockets

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
