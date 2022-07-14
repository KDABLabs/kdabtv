QT     += core gui widgets
CONFIG += c++17

SOURCES += \
    ../Step6/QWAMDelegate.cpp \
    ../Money.cpp \
    DataAndPercentageDelegate.cpp \
    Model.cpp \
    PercentageValue.cpp \
    main.cpp

HEADERS += \
    ../Step6/QWAMDelegate.h \
    ../Money.h \
    DataAndPercentageDelegate.h \
    EnumConverters.h \
    Model.h \
    PercentageValue.h

RESOURCES += \
    resources.qrc
