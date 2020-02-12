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
    width: 680
    height: 240

    Rectangle {
        anchors {
            verticalCenter: parent.verticalCenter
            left: parent.left
            leftMargin: 20
        }
        width:200; height:200
        id: focusBox
        property bool highlighted : focusArea.containsMouse
        color: highlighted ? "lightgreen" : "green"
        Text {
            anchors.centerIn: parent
            text: "Observe my color"
        }
    }

    Rectangle {
        anchors.centerIn: parent
        width: 200; height:200
        color: "yellow"
        MouseArea {
            anchors.fill:  parent
            id: focusArea
            hoverEnabled: true
        }
        Text {
            anchors.centerIn: parent
            text: "Move\ninto me"
        }
    }

    Rectangle {
        anchors {
            verticalCenter: parent.verticalCenter
            right: parent.right
            rightMargin: 20
        }
        width:200; height:200
        color: "black"

        MouseArea {
            id: clickArea
            anchors.fill:  parent
            onPressed: focusBox.highlighted = true
            onReleased: focusBox.highlighted = false
        }
        Text {
            color: "white"
            anchors.centerIn: parent
            text: "Click\nme"
        }
    }
}
