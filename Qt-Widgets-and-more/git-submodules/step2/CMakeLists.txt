cmake_minimum_required(VERSION 3.9)
project(MyApplication)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(MyApplication
  main.cpp
)

add_subdirectory(KDAlgorithms)
target_link_libraries(MyApplication kdalgorithms)

