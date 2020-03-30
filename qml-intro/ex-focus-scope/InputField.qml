/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

FocusScope {
    id: root
    property alias title: title.text
    implicitHeight: row.implicitHeight
    implicitWidth: row.implicitWidth

    Rectangle {
        id: focusIndicator
        anchors {
            fill: row
            margins: -2
        }
        color: "transparent"
        border {
            color: "black"
            width: 1
        }
        visible: root.activeFocus
    }

    Row {
        id: row
        spacing: 10
        anchors.verticalCenter: parent.verticalCenter

        Text {
            id: title
            anchors.verticalCenter: parent.verticalCenter
        }

        Rectangle {
            id: inputBackground
            anchors.verticalCenter: parent.verticalCenter
            width: Math.max(50, root.width - title.width - clearButton.width - row.spacing * 2)
            height: input.height + 10
            border {
                color: input.activeFocus ? "black" : color
                width: 3
            }
            color: "lightsteelblue"
            radius: 10

            TextInput {
                id: input
                focus: true
                anchors.centerIn : parent
                width: parent.width - 20
                clip: true

                KeyNavigation.right: clearButton
            }
        }

        Rectangle {
            id: clearButton
            anchors.verticalCenter: parent.verticalCenter
            width: clearButtonText.width + 10
            height: clearButtonText.height + 10
            border {
                color: activeFocus ? "black" : color
                width: 3
            }
            color: "gray"

            Text {
                id: clearButtonText
                anchors.centerIn: parent
                text: "Clear"
            }

            KeyNavigation.left: input
            Keys.onReturnPressed: input.text = ""
        }
    }
}

