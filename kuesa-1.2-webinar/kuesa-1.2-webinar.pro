TEMPLATE = app

TARGET = webinar

QT += kuesa

SOURCES += main.cpp \
    projectcoordinateshelper.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    projectcoordinateshelper.h

DEFINES += ASSETS=\\\"$$PWD/assets\\\"
