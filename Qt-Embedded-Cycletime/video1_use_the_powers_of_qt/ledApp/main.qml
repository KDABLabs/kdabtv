import QtQuick 2.15
import QtQuick.Window 2.15

Window {
    width: 1280
    height: 800
    visible: true
    title: qsTr("Embedded LED Control")

    Image {
        source: "qrc:///kdabtv.png"
        anchors.fill: parent

        DoubleCircle {
            id:  ring

            property int midX: 200
            property int midY: 200
            width: 400
            height: 400
            ringColor:  "#ff0084c8"

            anchors.centerIn: parent

            Repeater {
                id: ledRing

                model: 12
                delegate:  DoubleCircle {
                    id: led

                    ringColor: "#ff9ade00"
                    color: "#bbffffff"
                    Behavior on size {NumberAnimation {duration: 300}}

                    x: ring.midX + 200 * Math.cos( 2 * Math.PI / 12 * index) - width/2
                    y: ring.midY + 200 * Math.sin( 2 * Math.PI / 12 * index) - height/2

                    MouseArea{
                        anchors.fill: parent
                        hoverEnabled: true
                        onHoveredChanged:
                            if(containsMouse){
                                parent.size = 120
                                _ledController.setLED(index, parent.ringColor)
                            } else {
                                parent.size = 80
                                _ledController.setLED(index, Qt.rgba(0.01,0.01,0,1));
                            }
                    }
                }
            }

            DoubleCircle {
                anchors.centerIn: parent
                property int size: 100
                ringColor: "#ff222222"
                color: "#bbffffff"
                width: size
                height: size
                Behavior on size{ NumberAnimation {duration: 300}}
                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onHoveredChanged: if(containsMouse) {parent.size = 130} else { parent.size = 100}
                    onPressed: { _ledController.allOff(); }
                }
            }
        }
    }
}
