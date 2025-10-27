import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    id: window
    width: 1280
    height: 800
    visible: true
    title: qsTr("Embedded LED Control")

    Image {
        source: "qrc:///kdabtv.png"
        anchors.fill: parent

        Loader {
            id: mainLoader
            anchors.fill: parent
            source: "file://"+ _qmlPath+ "/AppContent.qml"
            scale: 0.5
        }

        Connections{
            target: _hotreload
            onWatchedSourceChanged: {
                mainLoader.active = false;
                _hotreload.clearCache();
                mainLoader.setSource("file://"+ _qmlPath+ "/AppContent.qml")
                mainLoader.active = true;
            }
        }
    }
}
