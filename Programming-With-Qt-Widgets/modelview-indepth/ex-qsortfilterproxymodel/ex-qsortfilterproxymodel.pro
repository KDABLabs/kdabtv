QT       += core gui widgets
CONFIG   += c++11

TARGET = sol-qsortfilterproxymodel
TEMPLATE = app


SOURCES += main.cpp \
    durationsortproxymodel.cpp \
    playlistmodel.cpp \
    videofilterproxymodel.cpp

HEADERS  += \
    durationsortproxymodel.h \
    playlistmodel.h \
    videofilterproxymodel.h

FORMS    +=

