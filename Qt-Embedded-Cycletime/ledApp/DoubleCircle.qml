import QtQuick 2.15
import QtQuick.Window 2.15

Rectangle {
    property color ringColor: "blue"
    property int size: 80

    width: size
    height: size
    border.width: 10
    radius: width

    color: "transparent"
    border.color: ringColor

    Rectangle {
        width: parent.width - 2 * parent.border.width
        height: parent.height - 2 * parent.border.width
        radius: width
        anchors.centerIn: parent

        border.width: parent.border.width
        border.color: Qt.lighter(parent.border.color)
        color: "transparent"
    }
}
