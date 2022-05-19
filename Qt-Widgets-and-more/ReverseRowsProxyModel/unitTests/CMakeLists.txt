cmake_minimum_required(VERSION 3.5)

project(ReverseRowsProxyModel LANGUAGES CXX)

enable_testing()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Test Core Gui Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Test Core Gui Widgets REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(ReverseRowsProxyModelTests tst_ReverseRowsProxyModel.cpp MasterSpy.cpp)
add_test(NAME ReverseRowsProxyModelTests COMMAND ReverseRowsProxyModelTests)

target_link_libraries(ReverseRowsProxyModelTests QWAMLib  Qt${QT_VERSION_MAJOR}::Test Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

