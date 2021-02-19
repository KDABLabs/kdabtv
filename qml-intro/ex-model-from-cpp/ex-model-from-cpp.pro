TEMPLATE = app
QT       += qml quick
SOURCES += cpp/main.cpp cpp/mymodel.cpp
HEADERS += cpp/mymodel.h
RESOURCES += resources.qrc

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml

DISTFILES += \
    pyqt/main.py \
    pyqt/mymodel.py \
    pyside/main.py \
    pyside/mymodel.py
