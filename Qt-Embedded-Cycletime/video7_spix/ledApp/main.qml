import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.0

Window {
    id: window
    width: 1280
    height: 800
    visible: true
    //visibility: Window.FullScreen
    title: qsTr("Embedded LED Control")

    Image {
        source: "qrc:///kdabtv.png"
        anchors.fill: parent

        Loader {
            id: mainLoader
            anchors.fill: parent
            source: "LoginPage.qml"
            scale: 1
        }

        Connections {
            target:  mainLoader.item
            onLogin: mainLoader.source = "AppContent.qml"
        }

        Connections{
            target: _hotreload
            onWatchedSourceChanged: {
                mainLoader.active = false;
                _hotreload.clearCache();
                mainLoader.setSource("AppContent.qml")
                mainLoader.active = true;
            }
        }
    }
}
