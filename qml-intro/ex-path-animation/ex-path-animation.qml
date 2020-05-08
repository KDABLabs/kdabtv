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
    id: window
    color: "black"
    width: 800
    height: 400

    Image {
        id : rocket
        source : "../images/rocket.png"
    }
    //--> slide
    PathAnimation {
        //--> hide
        id: pathAnim
        running: true
        duration: 3000
        loops: 10
        //<-- hide
        target: rocket
        orientation: PathAnimation.TopFirst
        anchorPoint: Qt.point(rocket.width/2,
                              rocket.height/2)

        path: Path {
            startX: 100; startY: window.height/2

            PathCubic {
                id: part1
                x: window.width - 100
                y: window.height/2
                control1X: 100; control1Y: 0
                control2X: x; control2Y: window.height
            }

            PathCubic { //--> collapse
                id: part2
                x: 100
                y: window.height/2
                control1X: window.width - 100; control1Y: 0
                control2X: x; control2Y: window.height
            } //<-- collapse
        }
    }
    //<-- slide

    // The remaining of the code is simply to show the curves and the control points

    // First part ----------------------------------------------------------------------------

    // C1
    Rectangle {
        color: "white"
        width:10; height:10
        x: part1.control1X-5; y: part1.control1Y-5
    }

    Text {
        text: "C1"
        color: "white"
        x: part1.control1X; y: part1.control1Y
        font.pointSize: 30
    }

    // C2
    Rectangle {
        color: "white"
        width:10; height:10
        x: part1.control2X-5; y: part1.control2Y-5
    }

    Text {
        text: "C2"
        color: "white"
        x: part1.control2X; y: part1.control2Y-50
        font.pointSize: 30
    }

    // The path
    PathView {
        anchors.fill: parent
        path: Path { startX: 100; startY: window.height/2; pathElements: part1 }
        model: 100
        delegate: Rectangle {
            width: 2; height: 2
            color: "white";
        }
    }

    // Second part ----------------------------------------------------------------------------

    // C1'
    Rectangle {
        color: "red"
        width:10; height:10
        x: part2.control1X-5; y: part2.control1Y-5
    }

    Text {
        text: "C1'"
        color: "red"
        x: part2.control1X; y: part2.control1Y
        font.pointSize: 30
    }

    // C2'
    Rectangle {
        color: "red"
        width:10; height:10
        x: part2.control2X-5; y: part2.control2Y-5
    }

    Text {
        text: "C2'"
        color: "red"
        x: part2.control2X; y: part2.control2Y-50
        font.pointSize: 30
    }

    // The path
    PathView {
        anchors.fill: parent
        path: Path { startX: window.width-100; startY: window.height/2; pathElements: part2 }
        model: 100
        delegate: Rectangle {
            width: 2; height: 2
            color: "red";
        }
    }
}
