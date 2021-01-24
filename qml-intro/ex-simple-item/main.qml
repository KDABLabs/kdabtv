/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

//--> slide
import Shapes 1.0

Item {
    width: 300; height: 200

    Ellipse {
        id: ellipse
        anchors.fill: parent
        anchors.margins: 50
//<-- slide
        color: "blue"
    }
    Timer {
        interval: 2000
        running: true
        onTriggered: ellipse.color = "red"
    }
}
