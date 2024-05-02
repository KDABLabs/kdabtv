cmake_minimum_required(VERSION 3.9)
project(UpdateUI)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Widgets)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
set(CMAKE_AUTOUIC TRUE)


add_executable(UpdateUI
  main.cpp
  Dashlet.ui
  Dashlet.h Dashlet.cpp Dashlet.ui
  KDSignalThrottler.h KDSignalThrottler.cpp
)
target_link_libraries(UpdateUI Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Widgets)
