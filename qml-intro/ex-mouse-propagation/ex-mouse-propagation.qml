/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 400; height: 200;
    color: "lightblue"

    Rectangle {
        x: 50
        y: 50
        width: 50
        height: 50

        color: "red"

        MouseArea {
            anchors.fill: parent
            onPressed: console.log("Lower rectangle pressed.");
            onReleased: console.log("Lower rectangle released.");
            onClicked: console.log("Lower rectangle clicked.");
        }
    }

    Rectangle {
        x: 75
        y: 75
        width: 50
        height: 50

        color: "yellow"

        // Play around with the commented out lines to see how the behaviour changes
        MouseArea {
            anchors.fill: parent
            //propagateComposedEvents: true
            onPressed: {
                //mouse.accepted = false;
                console.log("Upper rectangle pressed.");
            }
            onReleased: console.log("Upper rectangle released.");
            onClicked: {
                //mouse.accepted = false;
                console.log("Upper rectangle clicked.");
            }
        }
    }
}
