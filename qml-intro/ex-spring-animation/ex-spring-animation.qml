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
    color: "lightblue"
    width: 300; height: 300
//--> slide
    Rectangle {
        id: rect
        x: 100; y: 100
        width: 50; height: 50
        color: "red"

        Behavior on x { SpringAnimation { spring: 1; damping: 0.2 } }
        Behavior on y { SpringAnimation { spring: 2; damping: 0.2 } }
    }
//<-- slide
    MouseArea {
        anchors.fill: parent
        onClicked: {
            rect.x = mouse.x - rect.width/2
            rect.y = mouse.y - rect.height/2
        }
    }
}
