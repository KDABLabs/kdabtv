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
    width: 150; height: 200; color: "white"

    ListModel {
        id: nameModel
        ListElement { name: "Alice" }
        ListElement { name: "Bob" }
        ListElement { name: "Jane" }
        ListElement { name: "Victor" }
        ListElement { name: "Wendy" }
    }

    Component {
        id: nameDelegate
        Rectangle {
            id: top
            color: ListView.isCurrentItem ? "blue" : "transparent"
            height: text.implicitHeight
            anchors { left: parent.left; right: parent.right }
            Text {
                anchors.fill: parent
                id: text
                text: model.name
                color: parent.ListView.isCurrentItem ? "white" : "black"
                font.pixelSize: 32
                MouseArea {
                    anchors.fill: parent
                    onClicked: top.ListView.view.currentIndex = model.index
                }
            }
        }
    }

    ListView {
        anchors.fill: parent
        model: nameModel
        delegate: nameDelegate
        clip: true
    }
}
