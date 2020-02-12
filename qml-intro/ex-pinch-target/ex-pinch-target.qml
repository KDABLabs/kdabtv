/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Flickable {
    id: flick
    width: 400; height: 400
    contentWidth: 2000; contentHeight: 2000

    PinchArea {
        anchors.fill: parent
        pinch.target: img
        pinch.maximumScale: 1.0
        pinch.minimumScale: 0.1
        pinch.dragAxis: Pinch.XAndYAxis
    }

    Image {
        id: img
        width: flick.contentWidth
        height: flick.contentHeight
        source: "../images/rocket.svg"
    }
}

