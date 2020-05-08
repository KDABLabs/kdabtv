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
    id: window
    color: "black"
    width: 200
    height: 200

    //--> slide
    Flipable {
        id: flipable
        anchors.centerIn: parent
        property bool flipped: false

        front: Rectangle { //--> collapse
            color: "green"
            width: 100
            height: 100
            anchors.centerIn: parent
        } //<-- collapse
        back: Rectangle { //--> collapse
            color: "red"
            width: 100
            height: 100
            anchors.centerIn: parent
        } //<-- collapse

        transform: Rotation {
            axis.x: 1; axis.y: 0; axis.z: 0
            angle: flipable.flipped ? 180 : 0

            Behavior on angle {
                NumberAnimation { duration: 500 }
            }
        }
    }
    //<-- slide
    MouseArea {
        anchors.fill: parent
        onClicked: flipable.flipped = !flipable.flipped
    }
}
