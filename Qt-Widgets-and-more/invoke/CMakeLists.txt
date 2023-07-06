cmake_minimum_required(VERSION 3.9)
project(invoke)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(invoke
	main.cpp
        Foo.h Foo.cpp
	part1.cpp
	part2.cpp
	part3.cpp
	part4.cpp
	part5.cpp
	part6.cpp
	part7.cpp
	part8.cpp
	part9.cpp
	part10.cpp
)
