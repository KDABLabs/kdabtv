cmake_minimum_required(VERSION 3.9)
project(MyApplication)

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ ${CMAKE_MODULE_PATH})
include(CheckSubmoduleExists)
check_submodule_exists(kdalgorithms KDAlgorithms)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(MyApplication
  main.cpp
)

add_subdirectory(KDAlgorithms)
target_link_libraries(MyApplication kdalgorithms)

