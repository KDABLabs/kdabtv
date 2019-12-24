/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Image {
    id: image
    width: 1000; height: 1000
    source: "https://eoimages.gsfc.nasa.gov/images/imagerecords/74000/74393/world.topo.200407.3x5400x2700.jpg"
    fillMode: Image.PreserveAspectFit
    Rectangle {
        color: "red"
        anchors { left: parent.left; bottom: parent.bottom }
        height: 50
        width: parent.width * image.progress
        visible: image.progress != 1
    }

    onStatusChanged: console.log(sourceSize)
}

