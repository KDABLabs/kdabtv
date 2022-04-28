cmake_minimum_required(VERSION 3.5)

project(lessThan LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 CONFIG REQUIRED COMPONENTS Core)

add_executable(lessThan main.cpp step1.cpp step2.cpp step3.cpp step4.cpp step5.cpp step6.cpp step7.cpp step8.cpp step9.cpp)
target_link_libraries(lessThan Qt5::Core)
