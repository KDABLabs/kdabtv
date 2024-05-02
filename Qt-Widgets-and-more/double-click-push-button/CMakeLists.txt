cmake_minimum_required(VERSION 3.9)
project(double-click-push-button)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
add_executable(double-click-push-button
	main.cpp
        DoubleClickButton1.h DoubleClickButton1.cpp
        DoubleClickButton2.h DoubleClickButton2.cpp
        DoubleClickButton3.h DoubleClickButton3.cpp
        DoubleClickButton4.h DoubleClickButton4.cpp
        DoubleClickButton5.h DoubleClickButton5.cpp
        part1.cpp
	part2.cpp
	part3.cpp
	part4.cpp
        part5.cpp
)
target_link_libraries(double-click-push-button Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
