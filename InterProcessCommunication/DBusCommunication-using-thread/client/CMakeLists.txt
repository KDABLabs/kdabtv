set(PROJECT_SOURCES
    main.cpp
    widget.cpp
    widget.h
    widget.ui
    connection.h connection.cpp
    dbusworker.h dbusworker.cpp
    flags/flags.qrc
)

# This XML file was generated with the command
# qdbuscpp2xml -A ../server/peopleserver.h -t 'QVector<Person>=a{ssss}' -o ../shared/com.kdab.PeopleServerAPI.xml
# I added the -t feature for qdbuscpp2xml while working on this tutorial,
# so it didn't exist before Qt 6.3, see https://codereview.qt-project.org/c/qt/qtbase/+/366533
#
# To avoid depending on that version of Qt, we don't use qt_generate_dbus_interface but
# treat the XML as a source file and regenerate it manually when needed.
set(DBUSXML ../shared/com.kdab.PeopleServerAPI.xml)
set_source_files_properties(${DBUSXML} PROPERTIES INCLUDE person.h)
qt_add_dbus_interface(PROJECT_SOURCES ${DBUSXML} peopleserver_interface)

add_executable(ClientApplication
    ${PROJECT_SOURCES}
)

target_link_libraries(ClientApplication PRIVATE
    SharedCode
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::DBus
)

target_compile_features(ClientApplication PRIVATE cxx_std_11)
