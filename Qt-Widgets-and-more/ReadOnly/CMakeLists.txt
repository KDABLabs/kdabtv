cmake_minimum_required(VERSION 3.9)
project(ReadOnly)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)
add_executable(ReadOnly
    main.cpp
    part1.cpp
    Form.h Form.cpp Form.ui
    DepecheModel.h DepecheModel.cpp
    EnumConverters.h
    part2.cpp
    part3.cpp
    part4.cpp
    part5.cpp
    part6.cpp
    part7.cpp
    part8.cpp
)
target_link_libraries(ReadOnly Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)
