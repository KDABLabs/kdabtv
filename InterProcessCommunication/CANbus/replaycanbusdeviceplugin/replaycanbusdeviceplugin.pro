TEMPLATE = lib
TARGET = replaycanbus

QT = core serialbus

HEADERS += \
    replaycanbusdevice.h

SOURCES += \
    replaycanbusdevice.cpp \
    main.cpp

DISTFILES = plugin.json
