import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

import QtQuick.Window 2.1

Button {
    id: pageChangeButton
    Label {
        anchors.centerIn: bg
        text: "→"
        font.pixelSize: 30
        color: "white"
    }
    
    width: 90
    height: 90
    background:  Rectangle{
        id: bg
        width: parent.width
        height: parent.height
        radius: width/2
        color: colors.kdabBlue
        border.color: "white"
        border.width: 2
    }
    
    visible: view.currentIndex == 0
    onClicked: view.currentIndex = view.currentIndex+1
}
