/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 400; height: 200;
    color: "lightblue"

    Text {
        anchors.centerIn: parent
        text: "Press me"; font.pixelSize: 48
        color: mouseArea.pressed ? "green" : "black"

        MouseArea {
            id: mouseArea
            anchors.fill: parent
        }
    }
}
