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
    color: "black"
    width: child.width
    height: child.height

    Image {
        id: child
        source : "../images/vertical-gradient.png"
        anchors.fill: parent
        anchors.margins: 5
    }
}

