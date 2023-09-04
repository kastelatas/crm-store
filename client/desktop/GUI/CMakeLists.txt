cmake_minimum_required(VERSION 3.5)

project(GUI VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
   ${CMAKE_CURRENT_SOURCE_DIR}/ui
)

find_package(QT NAMES Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)
find_package(Qt5 COMPONENTS Core WebSockets REQUIRED)

add_subdirectory(icons)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        src/screens/Menu/menu.cpp    
        src/screens/Orders/orders.cpp
        src/screens/Ingredients/ingredients.cpp
        src/screens/Calculator/calculator.cpp
        src/screens/Clients/clients.cpp
        
        mainwindow.h
        src/screens/Menu/menu.h    
        src/screens/Orders/orders.h
        src/screens/Ingredients/ingredients.h
        src/screens/Calculator/calculator.h
        src/screens/Clients/clients.h

        defines/enums/MenuItems.hpp

        ui/mainwindow.ui
        ui/orders.ui
        ui/menu.ui
        ui/ingredients.ui
        ui/calculator.ui
        ui/clients.ui
)

add_executable(GUI)

target_sources(GUI PRIVATE ${PROJECT_SOURCES})

set_target_properties(GUI PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE)


target_link_libraries(GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets app Qt5::WebSockets)
