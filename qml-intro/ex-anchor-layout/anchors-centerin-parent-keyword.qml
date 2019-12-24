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
    // The parent element
    width: 400; height: 400
    color: "lightblue"

    Rectangle {
        color: "green"
        width: 50; height: 50
        anchors.centerIn: parent
    }
}
