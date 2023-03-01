import QtQuick 2.15
import QtQuick.Controls 2.0

Slider {
    id: control
    width: 50
    height: 455
    orientation: Qt.Vertical

    property alias pickedColor: sliderknob.color

    value: 0.3
    contentItem: Image{
        anchors.centerIn: parent

        width: 50
        height: parent.height - 50
        source: "qrc:///hsv-gradient.png"
    }

    handle: DoubleCircle {
        id: sliderknob
        y: control.topPadding + control.visualPosition * (control.availableHeight - height)

        anchors.horizontalCenter: parent.horizontalCenter
        color: Qt.hsla(0.95-control.visualPosition*0.95, 1.0, 0.5, 1.0)
        ringColor: "#ff2e3436"
        border.width: 5
        z:5
    }
}
