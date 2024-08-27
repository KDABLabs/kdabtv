set(CMAKE_INCLUDE_CURRENT_DIR_IN_INTERFACE TRUE)

add_library(SharedCode STATIC
    person.h person.cpp
    serverinterface.h serverinterface.cpp
)

target_link_libraries(SharedCode
     Qt${QT_VERSION_MAJOR}::Core
)
