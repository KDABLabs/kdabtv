cmake_minimum_required(VERSION 3.9)
project(episode2)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(episode2
	main.cpp
        specialization.cpp
        specialization_classes.cpp
        multiple_arguments.cpp
        no_default.cpp
	print_type.cpp
)
