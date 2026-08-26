cmake_minimum_required(VERSION 3.9)
project(replaycanbusdeviceplugin)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Core SerialBus)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)


add_library(replaycanbusdeviceplugin SHARED
  main.cpp
  replaycanbusdevice.cpp
  logs.qrc
)
target_link_libraries(replaycanbusdeviceplugin Qt6::Core Qt6::SerialBus)

set_target_properties(replaycanbusdeviceplugin 
    PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/plugins/canbus"
)
