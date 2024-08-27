set(PROJECT_SOURCES
        main.cpp

        basejob.cpp basejob.h
        personmatchjob.cpp personmatchjob.h
        countryflagjob.cpp countryflagjob.h

        widget.cpp
        widget.h
        widget.ui
        connection.h connection.cpp
        flags/flags.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(ClientApplication
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    add_executable(ClientApplication
        ${PROJECT_SOURCES}
    )
endif()

target_link_libraries(ClientApplication PRIVATE
    SharedCode
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Network
)

target_compile_features(ClientApplication PRIVATE cxx_std_11)

set_target_properties(ClientApplication PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(ClientApplication)
endif()

