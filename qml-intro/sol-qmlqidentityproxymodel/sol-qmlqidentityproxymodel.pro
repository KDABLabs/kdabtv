QT       += core gui quick
CONFIG   += c++11

TARGET = sol-qmlqidentityproxymodel
TEMPLATE = app

SOURCES += main.cpp \
    alluppercaseproxymodel.cpp \
    playlistmodel.cpp

HEADERS  += \
    alluppercaseproxymodel.h \
    playlistmodel.h

RESOURCES += \
    data.qrc
