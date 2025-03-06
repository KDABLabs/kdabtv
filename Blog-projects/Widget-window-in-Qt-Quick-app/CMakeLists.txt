cmake_minimum_required(VERSION 3.16)

project(WidgetWindowsInQtQuickApp VERSION 0.1 LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Quick Widgets)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appWidgetWindowsInQtQuickApp
    main.cpp
)

qt_add_qml_module(appWidgetWindowsInQtQuickApp
    URI WidgetWindowsInQtQuickApp
    VERSION 1.0
    QML_FILES
        Main.qml
        FontControlsQmlForm.qml
    SOURCES
        fontsbackend.h fontsbackend.cpp
        fontcontrolswidgetsform.h fontcontrolswidgetsform.cpp
        timer.h timer.cpp
        widgetFormHandler.h widgetFormHandler.cpp
        RESOURCES fontcontrolswidgetsform.ui fonts/OpenSans-Regular.ttf
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appWidgetWindowsInQtQuickApp PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER com.kdab.appWidgetWindowsInQtQuickApp
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appWidgetWindowsInQtQuickApp
    PRIVATE Qt6::Quick Qt6::Widgets)

include(GNUInstallDirs)
install(TARGETS appWidgetWindowsInQtQuickApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
