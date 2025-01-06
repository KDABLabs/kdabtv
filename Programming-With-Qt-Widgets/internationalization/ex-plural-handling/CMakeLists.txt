cmake_minimum_required(VERSION 3.19)
project(plural_handling)

find_package(Qt6 CONFIG REQUIRED COMPONENTS Core LinguistTools)
set(CMAKE_AUTOMOC TRUE)

add_executable(plural_handling
    main.cpp
)

target_link_libraries(plural_handling Qt6::Core)

qt_add_translations(TARGETS plural_handling
                    TS_FILES plural_handling_it.ts
                    PLURALS_TS_FILE plural_handling_en.ts)

