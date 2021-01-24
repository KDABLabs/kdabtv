QT       += qml quick
HEADERS   = \ 
    cpp/User.h
SOURCES   = cpp/main.cpp \
    cpp/User.cpp

# These next three lines makes the QML files show up in a section of their
# own in Qt Creator.
qml.files += $$files(*.qml)
qml.path = "."
INSTALLS += qml

OTHER_FILES += \
    main.qml

RESOURCES += \
    ex-exporting-object.qrc

DISTFILES += \
    pyqt/main.py \
    pyqt/user.py
