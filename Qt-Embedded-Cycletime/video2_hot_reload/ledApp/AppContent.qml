import QtQuick 2.15

Item {
    DoubleCircle {
        id:  ring

        property int midX: width/2
        property int midY: height/2
        width: 400
        height: 400
        ringColor:  "#ff0084c8"

        anchors.centerIn: parent

        Repeater {
            id: ledRing

            model: 12
            delegate: DoubleCircle {
                id: led

                ringColor: "#cc222222"
                color: "#bbffffff"
                Behavior on size {NumberAnimation {duration: 300}}

                x: ring.midX + ring.width/2 * Math.cos( 2 * Math.PI / 12 * index) - width/2
                y: ring.midY + ring.height/2 * Math.sin( 2 * Math.PI / 12 * index) - height/2

                MouseArea {
                    anchors.fill: parent
                    hoverEnabled: true
                    onHoveredChanged: {
                        if(containsMouse){
                            parent.size = 120
                            _ledController.setLED(index, slider.pickedColor)
                            parent.ringColor=slider.pickedColor
                        } else {
                            parent.size = 80
                            _ledController.setLED(index, Qt.hsva(slider.value, 1.0, 0.05, 1.0));
                            parent.ringColor=slider.pickedColor
                        }
                    }
                }
            }
        }

        DoubleCircle {
            anchors.centerIn: parent
            property int size: 100
            ringColor: "#ff222222"
            color: Qt.darker("white")
            width: size
            height: size
            Behavior on size{ NumberAnimation {duration: 300}}
            MouseArea {
                anchors.fill: parent
                hoverEnabled: true
                onHoveredChanged: if(containsMouse) {parent.size = 100} else { parent.size = 100}
                onPressed: { _ledController.allOff(); }
            }
        }
    }

    ColorSlider
    {
        id: slider0
        anchors.left: parent.left
        value: 0.0
        anchors.verticalCenter: parent.verticalCenter
    }

    ColorSlider
    {
        id: slider
        anchors.right: parent.right
        value: 0.5
        anchors.verticalCenter: parent.verticalCenter
    }
}
