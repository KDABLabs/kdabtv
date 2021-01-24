QT       += qml quick
HEADERS   = cpp/ellipseitem.h
RESOURCES = ex-simple-item.qrc
SOURCES   = \
    cpp/ellipseitem.cpp \
    cpp/main.cpp

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml

DISTFILES += \
    pyqt/main.py \
    pyqt/ellipseitem.py \
    pyside/main.py \
    pyside/ellipseitem.py
