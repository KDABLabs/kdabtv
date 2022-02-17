QT += quick

CONFIG += c++11

!versionAtLeast(QT_VERSION, 5.15.0) {
    message("Cannot use Qt $${QT_VERSION}")
    error("Use Qt 5.15 or newer")
}

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

android: {
    QT += androidextras
}

SOURCES += \
        firebase.cpp \
        main.cpp

HEADERS += \
  firebase.h

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
  android/AndroidManifest.xml \
  android/build.gradle \
  android/gradle.properties \
  android/gradle/wrapper/gradle-wrapper.jar \
  android/gradle/wrapper/gradle-wrapper.properties \
  android/gradlew \
  android/gradlew.bat \
  android/res/values/libs.xml \
  qtquickcontrols2.conf

DISTFILES += android/google-services.json

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

android|ios {
    SOURCES += \
        firebase-qt/src/firebaseqtapp.cpp \
        firebase-qt/src/firebaseqtmessaging.cpp \
        firebase-qt/src/firebaseqtabstractmodule.cpp

    HEADERS += \
        firebase-qt/src/firebaseqtabstractmodule.h \
        firebase-qt/src/firebaseqtapp.h \
        firebase-qt/src/firebaseqtapp_p.h \
        firebase-qt/src/firebaseqtmessaging.h
}

# This is the path for the Firebase C++ SDK
GOOGLE_FIREBASE_SDK = $$PWD/../firebase_cpp_sdk

# This is the path for the iOS Firebase SDK
GOOGLE_IOS_FIREBASE_SDK = $$PWD/../Firebase

INCLUDEPATH += $${GOOGLE_FIREBASE_SDK}/include
DEPENDPATH += $${GOOGLE_FIREBASE_SDK}/include

contains(ANDROID_TARGET_ARCH,armeabi-v7a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    LIBS += -L$${GOOGLE_FIREBASE_SDK}/libs/android/armeabi-v7a/c++/ -lfirebase_app -lfirebase_messaging

    PRE_TARGETDEPS += $${GOOGLE_FIREBASE_SDK}/libs/android/armeabi-v7a/c++/libfirebase_app.a
    PRE_TARGETDEPS += $${GOOGLE_FIREBASE_SDK}/libs/android/armeabi-v7a/c++/libfirebase_messaging.a
}

contains(ANDROID_TARGET_ARCH,arm64-v8a) {
    ANDROID_PACKAGE_SOURCE_DIR = \
        $$PWD/android

    LIBS += -L$${GOOGLE_FIREBASE_SDK}/libs/android/arm64-v8a/c++/ -lfirebase_app -lfirebase_messaging

    PRE_TARGETDEPS += $${GOOGLE_FIREBASE_SDK}/libs/android/arm64-v8a/c++/libfirebase_app.a
    PRE_TARGETDEPS += $${GOOGLE_FIREBASE_SDK}/libs/android/arm64-v8a/c++/libfirebase_messaging.a
}

ios: {
    GOOGLE_FIREBASE_SDK_LIBS_PATH = $${GOOGLE_FIREBASE_SDK}/libs/ios/universal/
    GOOGLE_FIREBASE_SDK_FW_PATH = $${GOOGLE_FIREBASE_SDK}/frameworks/ios/universal/

    QMAKE_INFO_PLIST = ios/Info.plist

    DISTFILES += \
        ios/Info.plist \
        ios/GoogleService-Info.plist \

    # You must deploy your Google Play config file
    deployment.files = ios/GoogleService-Info.plist
    deployment.path =
    QMAKE_BUNDLE_DATA += deployment

    QMAKE_LFLAGS += -ObjC

    LIBS += \
        -L$${GOOGLE_FIREBASE_SDK_LIBS_PATH}

    LIBS +=  \
        -framework StoreKit \
        -F$${GOOGLE_IOS_FIREBASE_SDK}/Analytics \
        -framework FirebaseAnalytics \
        -framework FirebaseCore \
        -framework FirebaseCoreDiagnostics \
        -framework FirebaseInstanceID \
        -framework GoogleDataTransport \
        -framework GoogleDataTransportCCTSupport \
        -framework GoogleAppMeasurement \
        -framework GoogleUtilities \
        -framework nanopb

    LIBS +=  \
       -F$${GOOGLE_IOS_FIREBASE_SDK}/Messaging \
       -framework FirebaseMessaging \
       -framework Protobuf \
       -framework UserNotifications

    LIBS +=  \
       -F$${GOOGLE_FIREBASE_SDK_FW_PATH} \
       -framework firebase_messaging \
       -framework firebase
}
