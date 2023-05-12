cmake_minimum_required(VERSION 3.9)
project(timers)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
add_executable(timers
	main.cpp
	part1.cpp
	part2.cpp
)
target_link_libraries(timers Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui  Qt${QT_VERSION_MAJOR}::Widgets)
