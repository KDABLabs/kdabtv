/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0
import Shapes 5.0

Item {
    width: 300; height: 200

    Ellipse {
        width: 150; height: 100
        anchors.centerIn: parent
        color: "blue"

        Text {
            anchors.centerIn: parent
            text: parent.color
        }
    }
}
