/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

//--> slide
import QtQuick 2.0

Rectangle {
    width: 1000; height: 1000; color: "lightblue"

    MultiPointTouchArea {
        anchors.fill: parent
        minimumTouchPoints: 1
        maximumTouchPoints: 3

        touchPoints: [
            TouchPoint { id: touch1 },
            TouchPoint { id: touch2 },
            TouchPoint { id: touch3 }
        ]
    }

    Rectangle {
        x: touch1.x - width/2; y: touch1.y - height/2
        width: 200; height: 200
        visible: touch1.pressed
        color: "cyan"
    }
    Rectangle {//--> collapse
        x: touch2.x - width/2; y: touch2.y - height/2
        width: 200; height: 200
        visible: touch2.pressed
        color: "blue"
    }//<-- collapse
    Rectangle {//--> collapse
        x: touch3.x - width/2; y: touch3.y - height/2
        width: 200; height: 200
        visible: touch3.pressed
        color: "red"
    }//<-- collapse
}
//<-- slide
