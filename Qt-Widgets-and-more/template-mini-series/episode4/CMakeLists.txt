cmake_minimum_required(VERSION 3.9)
project(episode4)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(episode4
	main.cpp
	final_test.cpp
        transform_basic.cpp
	transform_cpp17.cpp
	transform_cpp14.cpp
)
