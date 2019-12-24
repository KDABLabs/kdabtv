/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 400; height: 400; color: "lightblue"

    Image {
        source: "../images/arrow.svg"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
    }
    Image {
        id: south
        source: "../images/arrow.svg"
        transform: Rotation { origin.x: south.width/2;
                              origin.y: south.height/2; angle: 180 }
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
    }
}
