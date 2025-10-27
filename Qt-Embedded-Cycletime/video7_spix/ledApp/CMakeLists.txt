cmake_minimum_required(VERSION 3.14)

project(ledApp LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Quick  REQUIRED)
find_package(Qt6 6.2 COMPONENTS Quick Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick SerialPort REQUIRED)

# CHRISTOPH Spix CMake is a bit broken and needs to be told its own modules
LIST(APPEND CMAKE_MODULE_PATH /home/christoph/KDAB/spix/cmake/modules)
find_package(Spix REQUIRED)

if(ANDROID)
      add_library(ledApp SHARED
      main.cpp
      qml.qrc
    )
else()
      add_executable( ledApp
      main.cpp
      ledcontroller.cpp
      ledcontroller.h
      hotreload.cpp
      hotreload.h
      qml.qrc
    )
endif()

target_compile_definitions(ledApp
  PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(ledApp
  PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Quick Qt${QT_VERSION_MAJOR}::SerialPort Spix::Spix)
