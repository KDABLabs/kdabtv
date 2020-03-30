/*************************************************************************
 *
 * Copyright (c) 2014-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Item {
    property bool checked: false

    width: textItem.width + checkImage.width
    height: checkImage.height

    Image {
        id: checkImage
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        source: parent.checked ? "checked.svg" : "unchecked.svg"
    }

    Text {
        id: textItem
        anchors.left: checkImage.right
        anchors.leftMargin: 4
        anchors.verticalCenter: checkImage.verticalCenter
        text: "Option"
        font.pixelSize: checkImage.height - 4
    }

    MouseArea {
        anchors.fill: parent
        onClicked: parent.checked = !parent.checked
    }
}
