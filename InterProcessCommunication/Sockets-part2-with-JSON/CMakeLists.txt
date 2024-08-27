cmake_minimum_required(VERSION 3.5)

project(Sockets-part2-with-JSON VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets Network REQUIRED)
# Qt >= 5.15 required for QLocalSocket::errorOccurred
find_package(Qt${QT_VERSION_MAJOR} 5.15 COMPONENTS Widgets Network REQUIRED)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")

add_subdirectory(shared)
add_subdirectory(client)
add_subdirectory(server)
