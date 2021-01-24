QT += quick

HEADERS = \
    User.h \
    UserList.h

SOURCES = \
    main.cpp \
    User.cpp \
    UserList.cpp

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml

OTHER_FILES += \
    main.qml

RESOURCES += \
    ex-object-ownership.qrc
