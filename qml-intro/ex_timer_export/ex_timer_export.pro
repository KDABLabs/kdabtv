QT += qml quick

SOURCES += cpp/main.cpp \
    cpp/randomtimer.cpp

HEADERS += \
    cpp/randomtimer.h

RESOURCES += \
    resources.qrc

OTHER_FILES += main.qml

DISTFILES += \
    pyqt/main.py \
    pyqt/randomtimer.py \
    pyside/main.py \
    pyside/randomtimer.py
