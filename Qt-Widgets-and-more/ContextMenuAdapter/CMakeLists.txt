cmake_minimum_required(VERSION 3.9)
set(CMAKE_CXX_STANDARD 17)

project(ContextMenuAdapter)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Gui Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)


add_executable(ContextMenuAdapter
    main.cpp
    QWAMTableView.h
    QWAMTreeView.h
    CustomContextMenuAdapter.h CustomContextMenuAdapter.cpp
    CustomContextMenuAction.h CustomContextMenuAction.cpp
)
target_link_libraries(ContextMenuAdapter Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Widgets)

add_definitions(-DVERSION=2)
