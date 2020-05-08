/*************************************************************************
 *
 * Copyright (c) 2010-2011, Nokia Corporation and/or its subsidiary(-ies).
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 150; height: 150; color: "black"

    Image {
        id: rocket
        anchors.centerIn: parent
        source: "../images/rocket.svg"
    }

    states: [
        State { name: "up"
                PropertyChanges { target: rocket; rotation: 0 } },
        State { name: "down"
                PropertyChanges { target: rocket; rotation: 180 } }
    ]

    state: "up"

    transitions: [
        Transition {
            from: "*"; to: "*"
            PropertyAnimation {
                target: rocket
                properties: "rotation"; duration: 1000
            }
        }
    ]
    MouseArea { anchors.fill: parent
                onClicked: parent.state === "up" ?
                    parent.state = "down" : parent.state = "up" }
}
