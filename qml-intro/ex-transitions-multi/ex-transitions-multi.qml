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
    width: 150; height: 360
    color: "black"

    Rectangle {
        id: redLight
        x: 25; y: 15; width: 100; height: 100
        radius: 50
    }
    Rectangle {
        id: yellowLight
        x: 25; y: 130; width: 100; height: 100
        radius: 50
    }
    Rectangle {
        id: greenLight
        x: 25; y: 245; width: 100; height: 100
        radius: 50
    }
    states: [
        State {
            name: "stopState"
            PropertyChanges { target: redLight; color: "red" }
            PropertyChanges { target: yellowLight; color: "lightGray" }
            PropertyChanges { target: greenLight; color: "lightGray" }
        },
        State {
            name: "waitState"
            PropertyChanges { target: redLight; color: "red" }
            PropertyChanges { target: yellowLight; color: "yellow" }
            PropertyChanges { target: greenLight; color: "lightGray" }
        },
        State {
            name: "driveState"
            PropertyChanges { target: redLight; color: "lightGray" }
            PropertyChanges { target: yellowLight; color: "lightGray" }
            PropertyChanges { target: greenLight; color: "green" }
        },
        State {
            name: "slowState"
            PropertyChanges { target: redLight; color: "lightGray" }
            PropertyChanges { target: yellowLight; color: "yellow" }
            PropertyChanges { target: greenLight; color: "lightGray" }
        }
    ]
    state: "stopState"

    Timer {
        interval: 1000
        repeat: true
        running: true
        onTriggered: {
            var states = ["stopState", "waitState", "driveState", "slowState"]
            var nextIndex = ( states.indexOf(parent.state) + 1 ) % states.length
            parent.state = states[nextIndex]
        }
    }
    //--> slide
    transitions: [
        Transition {
            from: "*"; to: "*"
            PropertyAnimation {
                targets: [redLight, yellowLight, greenLight]
                properties: "color"; duration: 100
            }
        } ]
    //<-- slide
}
