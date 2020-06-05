/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 150; height: 200; color: "white"

    ListModel {
        id: nameModel
        ListElement { name: "Alice" }
        ListElement { name: "Bob" }
        ListElement { name: "Jane" }
        ListElement { name: "Victor" }
        ListElement { name: "Wendy" }
    }

    Component {
        id: nameDelegate
        Text {
            text: model.name
            font.pixelSize: 32
        }
    }

    Column {
        anchors.fill: parent
        Repeater {
            model: nameModel
            delegate: nameDelegate
        }
    }
}
