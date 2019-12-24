/*************************************************************************
 *
 * Copyright (c) 2018-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    id: background
    width: 300; height: 100
    color: "lightblue"

    Rectangle {
        color: "green"
        height: 50
        anchors.top: background.top

        anchors.left: background.left
        anchors.right: background.right
    }
}
