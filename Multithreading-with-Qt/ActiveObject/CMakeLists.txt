cmake_minimum_required(VERSION 3.5)

# Code for the video "Multithreading with Qt (Part 3)"
project(ActiveObject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} 5.15 COMPONENTS Widgets Network REQUIRED)

add_executable(ActiveObject activeObject.cpp)
target_link_libraries(ActiveObject Qt::Core)
