cmake_minimum_required(VERSION 3.9)
project(episode1)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
add_executable(episode1
	main.cpp
        basic_min_method.cpp
        template_min_method.cpp
        template_stack.cpp
        template_stackV2.cpp
        stack_container_type.cpp
        stack_container_typeV2.cpp
)
