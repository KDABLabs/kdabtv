cmake_minimum_required(VERSION 3.9)
project(canbusexample)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Core SerialBus)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)


add_executable(canbusexample
  main.cpp
  tccharger.cpp
  tcchargercontroller.cpp
)
target_link_libraries(canbusexample Qt6::Core Qt6::SerialBus)

add_subdirectory(replaycanbusdeviceplugin)
