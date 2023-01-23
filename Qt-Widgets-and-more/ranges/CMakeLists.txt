cmake_minimum_required(VERSION 3.9)
project(ranges)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Gui)
set(CMAKE_AUTOMOC TRUE)
set(CMAKE_AUTORCC TRUE)
add_executable(ranges
	main.cpp
        01_simple.cpp
        02_pairs.cpp
        03_pairsV2.cpp
        04_structured_bindings.cpp
        05_structured_bindings_qt.cpp
        06_structured_bindings_my_struct.cpp
        07_structured_bindings_my_class.cpp
        08_stl_map_in_loops.cpp
        09_qt_map_in_loops.cpp
        10_qt_map_in_loops-with-ranges.cpp
)
target_link_libraries(ranges Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui)
