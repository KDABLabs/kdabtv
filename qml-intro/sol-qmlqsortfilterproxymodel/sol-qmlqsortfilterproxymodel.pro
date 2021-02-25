QT       += core gui quick
CONFIG   += c++11

TARGET = sol-qmlqsortfilterproxymodel
TEMPLATE = app

SOURCES += main.cpp \
    durationsortproxymodel.cpp \
    playlistmodel.cpp \
    videofilterproxymodel.cpp

HEADERS  += \
    durationsortproxymodel.h \
    playlistmodel.h \
    videofilterproxymodel.h

RESOURCES += \
    data.qrc
