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
    width: 300; height: 150; color: "white"

    ListModel {
        id: nameModel
        ListElement { file: "../images/rocket.svg"
                      name: "rocket" }
        ListElement { file: "../images/clear.svg"
                      name: "clear" }
        ListElement { file: "../images/arrow.svg"
                      name: "arrow" }
        ListElement { file: "../images/book.svg"
                      name: "book" }
    }
    //--> slide
    Component {
        id: nameDelegate
        Column {
            opacity: PathView.opacity
            z: PathView.z
            scale: PathView.scale
            Image { //--> collapse
                anchors.horizontalCenter: delegateText.horizontalCenter
                source: model.file; width: 64; height: 64; smooth: true
                fillMode: Image.PreserveAspectFit
            }//<-- collapse
            Text {//--> collapse
                id: delegateText
                text: model.name; font.pixelSize: 24
            }//<-- collapse
        }
    }
    //<-- slide

    PathView {
        anchors.fill: parent
        model: nameModel
        delegate: nameDelegate
        focus: true

        path: Path {
            // Front
            startX: 150; startY: 100
            PathAttribute { name: "opacity"; value: 1.0 }
            PathAttribute { name: "scale"; value: 1.0 }
            PathAttribute { name: "z"; value: 0 }

            // Left
            PathCubic { x: 50; y: 50; control1X: 100; control1Y: 100
                                       control2X: 50; control2Y: 75 }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathAttribute { name: "scale"; value: 0.5 }
            PathAttribute { name: "z"; value: -1 }

            // Top
            PathCubic { x: 150; y: 20; control1X: 50; control1Y: 35
                                        control2X: 100; control2Y: 20 }
            PathAttribute { name: "opacity"; value: 0.25 }
            PathAttribute { name: "scale"; value: 0.25 }
            PathAttribute { name: "z"; value: -2 }

            // Right
            PathCubic { x: 250; y: 50; control1X: 200; control1Y: 20
                                        control2X: 250; control2Y: 35 }
            PathAttribute { name: "opacity"; value: 0.5 }
            PathAttribute { name: "scale"; value: 0.5 }
            PathAttribute { name: "z"; value: -1 }

            PathCubic { x: 150; y: 100; control1X: 250; control1Y: 75
                                        control2X: 200; control2Y: 100 }
        }
        highlight: Rectangle {
            radius: 4
            width: 10; height: 10
            color: "lightblue"
        }
        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()
    }
}
