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
    width: 150; height: 220; color: "white"

    ListModel {
        id: nameModel
        ListElement { name: "Alice" }
        ListElement { name: "Bob" }
        ListElement { name: "Jane" }
        ListElement { name: "Harry" }
        ListElement { name: "Wendy" }
    }

    Component {
        id: nameDelegate
        Text {
            readonly property ListView __lv: ListView.view
            width: parent.width
            text: model.name;
            font.pixelSize: 32


            MouseArea {
                anchors.fill: parent
                onClicked: __lv.currentIndex = model.index
            }
        }
    }
//--> slide
    ListView {
        anchors.fill: parent
        model: nameModel
        delegate: nameDelegate
        focus: true
        clip: true
        header: Rectangle {
            anchors { left: parent.left; right: parent.right }
            height: 10
            color: "pink"
        }
        footer: Rectangle {
            anchors { left: parent.left; right: parent.right }
            height: 10
            color: "lightblue"
        }
        highlight: Rectangle {
            anchors { left: parent.left; right: parent.right }
            color: "lightgray"
        }
    }
//<-- slide
}
