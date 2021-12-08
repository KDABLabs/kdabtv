project(Debugging-cmake)
cmake_minimum_required(VERSION 3.9)
find_package(Qt5 CONFIG REQUIRED COMPONENTS Core)

add_executable(Debugging-cmake
  main.cpp
)
target_link_libraries(Debugging-cmake Qt5::Core)
target_precompile_headers(Debugging-cmake PUBLIC QWAM_pch.h) # With PUBLIC they will be used by targets using this target
