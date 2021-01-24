QT       += quick
SOURCES   = main.cpp
RESOURCES += ex-simple-types.qrc

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml


