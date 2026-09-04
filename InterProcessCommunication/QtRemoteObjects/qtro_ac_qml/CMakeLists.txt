cmake_minimum_required(VERSION 3.16)

project(qtro_ac_qml VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt6 REQUIRED COMPONENTS Quick RemoteObjects)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appqtro_ac_qml
    main.cpp
)

qt_add_qml_module(appqtro_ac_qml
    URI qtro_ac_qml
    VERSION 1.0
    QML_FILES
        Main.qml
)
qt_add_repc_replicas(appqtro_ac_qml ../qtro_server/Sensors.rep)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appqtro_ac_qml PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appqtro_ac_qml
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appqtro_ac_qml
    PRIVATE Qt::Quick Qt::RemoteObjects
)

include(GNUInstallDirs)
install(TARGETS appqtro_ac_qml
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
