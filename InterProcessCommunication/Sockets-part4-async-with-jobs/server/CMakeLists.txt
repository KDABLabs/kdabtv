set(PROJECT_SOURCES
        main.cpp
        peopleserver.h peopleserver.cpp
        clienthandler.h clienthandler.cpp
        database.h database.cpp
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PeopleServer
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(PeopleServer
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(PeopleServer PRIVATE
    SharedCode
    Qt${QT_VERSION_MAJOR}::Network
)

target_compile_features(PeopleServer PRIVATE cxx_std_11)

set_target_properties(PeopleServer PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PeopleServer)
endif()

