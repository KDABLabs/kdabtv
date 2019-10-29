/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Item {
    width: 300
    height: 115

    Text {
        id: textElement
        x: 50
        y: 25
        text: "Qt Quick"
        font.family: "Helvetica"
        font.pixelSize: 50
    }

    Rectangle {
        x: 50
        y: 75
        height: 5
        width: textElement.width
        color: "green"
    }
}
