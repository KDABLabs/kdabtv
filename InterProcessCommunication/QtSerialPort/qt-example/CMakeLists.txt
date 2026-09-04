cmake_minimum_required(VERSION 3.16)

project(qt-example VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick SerialPort)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(qt-example
    main.cpp
)

qt_add_qml_module(qt-example
    URI qt-example
    VERSION 1.0
    QML_FILES
        Main.qml
    SOURCES
        commandinterface.h
        commandinterface.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(qt-example PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.qt-example
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(qt-example
    PRIVATE Qt6::Quick Qt6::SerialPort
)

include(GNUInstallDirs)
install(TARGETS qt-example
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
