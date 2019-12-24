/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    // The parent element
    width: 400; height: 400
    color: "lightblue"

    Rectangle {
        color: "green"
        anchors.fill: parent
        anchors.margins: 10
    }
}
