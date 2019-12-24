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
        y: 25 //overwritten by the top anchor
        height: 50; width: 50
        anchors.right: background.right
        anchors.top: background.top
    }
}
