add_executable(PeopleDBusServer
    main.cpp
    database.h database.cpp
    peopleserver.h peopleserver.cpp
)

target_link_libraries(PeopleDBusServer
    PRIVATE
        SharedCode
        Qt${QT_VERSION_MAJOR}::DBus
)

target_compile_features(PeopleDBusServer PRIVATE cxx_std_11)

