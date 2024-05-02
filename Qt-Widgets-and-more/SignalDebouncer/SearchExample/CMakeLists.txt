cmake_minimum_required(VERSION 3.9)
project(SearchExample)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Widgets Gui)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)
add_executable(SearchExample
	main.cpp
        SearchWindow.h SearchWindow.cpp SearchWindow.ui
        KDSignalThrottler.h KDSignalThrottler.cpp
        resources.qrc
)
target_link_libraries(SearchExample Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Gui)
