cmake_minimum_required(VERSION 3.9)
project(UnitTests)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 Qt6 CONFIG REQUIRED COMPONENTS Core Test)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Test)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)

add_library(QWAMLib SHARED Gadgets.h NewWay.h NewWayUsingNameSpace.h OriginalWay.h)
target_link_libraries(QWAMLib Qt${QT_VERSION_MAJOR}::Core)

add_executable(QWAM main.cpp)
target_link_libraries(QWAM QWAMLib)

add_subdirectory(Tests)
