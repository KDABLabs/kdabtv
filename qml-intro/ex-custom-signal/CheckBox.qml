/*************************************************************************
 *
 * Copyright (c) 2010, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

//--> slide
Item {
    // define signal
    signal checked(bool checkValue)

    //--> hide
    width: textItem.width + checkImage.width
    height: checkImage.height

    Image {
        id: checkImage
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        source: toggleArea.__checked ? "checked.svg" : "unchecked.svg"
    }

    Text {
        id: textItem
        anchors.left: checkImage.right
        anchors.leftMargin: 4
        anchors.verticalCenter: checkImage.verticalCenter
        text: "Option"
        font.pixelSize: checkImage.height - 4
    }

    //<-- hide
    MouseArea {
        id: toggleArea
        anchors.fill: parent

        // define internal state property
        property bool __checked: false

        onClicked: {
            __checked = !__checked;

            parent.checked(__checked);  // emit signal with new value
        }
    }
}
//<-- slide
