/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 400; height: 300;
    color: "lightblue"

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y: 40
        height: parent.height / 2
        text: "Press me"
        font.pixelSize: 48

        MouseArea {
            anchors.fill: parent
            onPressed: parent.color = "green"
            onReleased: parent.color = "black"
        }
    }

    Text {
        anchors.horizontalCenter: parent.horizontalCenter
        y: parent.height / 2 + 40
        height: parent.height / 2
        text: "Click me"
        font.pixelSize: 48

        MouseArea {
            anchors.fill: parent
            onClicked: parent.font.bold = !parent.font.bold
        }
    }
}
