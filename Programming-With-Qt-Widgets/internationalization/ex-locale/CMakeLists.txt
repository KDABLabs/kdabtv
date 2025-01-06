cmake_minimum_required(VERSION 3.19)
project(ex-locale)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Core)
set(CMAKE_AUTOMOC TRUE)

add_executable(ex-locale main.cpp)

target_link_libraries(ex-locale Qt6::Core)

