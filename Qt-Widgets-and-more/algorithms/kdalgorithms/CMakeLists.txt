cmake_minimum_required(VERSION 3.9)
project(kdalgorithms)

add_library(kdalgorithms INTERFACE)
target_include_directories(kdalgorithms INTERFACE src/)

include(CTest)

if (CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
  set(MAIN_PROJECT ON)
endif()

option(KDALGORITHMS_BUILD_TEST "Build the kdalgorithms unit tests when BUILD_TESTING is enabled." ${MAIN_PROJECT})

if(BUILD_TESTING AND ${KDALGORITHMS_BUILD_TEST})

    # This library support C++14 and above.
    if (NOT DEFINED CMAKE_CXX_STANDARD)
        set(CMAKE_CXX_STANDARD 20)
    endif()

    add_compile_options(-Wall)

    if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pedantic -Werror -Wno-deprecated -Wextra -Woverloaded-virtual -Winit-self -Wmissing-include-dirs -Wunused -Wno-div-by-zero -Werror=undef -Wpointer-arith -Wmissing-noreturn -Werror=return-type -Wsuggest-override")
    endif()

    if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wunused-parameter")
    endif()

    if(MSVC) # Check if we are using the Visual Studio compiler
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:__cplusplus") # Make __cplusplus match the actual C++ version used
    endif()


    # Needed for the unit tests
    find_package(QT NAMES Qt6 Qt5 COMPONENTS Core Gui Widgets REQUIRED)
    find_package(Qt${QT_VERSION_MAJOR} CONFIG REQUIRED COMPONENTS Core Test)
    set(CMAKE_AUTOMOC TRUE)

    enable_testing()
    add_executable(tst_kdalgorithms
        src/kdalgorithms.h

        src/bits/copy_or_move_iterators.h
        src/bits/filter.h
        src/bits/has_reserve_trait.h
        src/bits/operators.h
        src/bits/return_type_trait.h
        src/bits/shared.h
        src/bits/transform.h

        tests/tst_kdalgorithms.cpp
        tests/tst_constraints.cpp
        tests/copy_observer.h
        tests/copy_observer.cpp
    )

    add_test(NAME tst_kdalgorithms COMMAND tst_kdalgorithms)
    target_link_libraries(tst_kdalgorithms Qt${QT_VERSION_MAJOR}::Test)

    add_executable(tst_return_type_traits tests/tst_return_type_traits.cpp)

    # Make it show up in Qt Creator
    add_custom_target(additional_files SOURCES README.md run)
endif()
