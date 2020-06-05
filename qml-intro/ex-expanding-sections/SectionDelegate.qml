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
    color: "#b0dfb0"
    implicitHeight: txt.implicitHeight + 4

    property alias text: txt.text

    signal clicked()

    Text {
        id: txt
        anchors.centerIn: parent
        font.pixelSize: 16
        font.bold: true
    }
    MouseArea {
        anchors.fill: parent
        onClicked: parent.clicked()
    }
}
