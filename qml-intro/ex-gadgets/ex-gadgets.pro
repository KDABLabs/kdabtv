QT       += quick
SOURCES   = main.cpp Person.cpp Database.cpp
HEADERS += Person.h Database.h
RESOURCES += ex-gadgets.qrc

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml


