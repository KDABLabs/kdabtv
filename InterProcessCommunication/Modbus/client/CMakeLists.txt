cmake_minimum_required(VERSION 3.9)
project(client)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(Qt6 CONFIG REQUIRED COMPONENTS Core SerialBus OPTIONAL_COMPONENTS SerialPort)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)


add_executable(client
  main.cpp
  modbusdeviceconnector.cpp
  p30evseconnector.cpp
)

if (TARGET Qt6::SerialPort)
    target_link_libraries(client Qt6::SerialPort)
endif()

target_link_libraries(client Qt6::Core Qt6::SerialBus)
