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
    width: 300; height: 250; color: "white"

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

    Component {
        id: nameDelegate
        Column {
            Image {
                anchors.horizontalCenter: delegateText.horizontalCenter
                source: model.file; width: 64; height: 64; smooth: true
                fillMode: Image.PreserveAspectFit
            }
            Text {
                id: delegateText
                text: model.name; font.pixelSize: 24
            }
        }
    }
    //--> slide
    PathView {
        anchors.fill: parent
        model: nameModel
        delegate: nameDelegate
        focus: true

        path: Path {//--> collapse
            startX: 150; startY: 200
            PathCubic { x: 50; y: 100; control1X: 100; control1Y: 200
                                       control2X: 50; control2Y: 125 }
            PathCubic { x: 150; y: 50; control1X: 50; control1Y: 75
                                       control2X: 100; control2Y: 50 }
            PathCubic { x: 250; y: 100; control1X: 200; control1Y: 50
                                        control2X: 250; control2Y: 75 }
            PathCubic { x: 150; y: 200; control1X: 250; control1Y: 125
                                        control2X: 200; control2Y: 200 }
        }//<-- collapse

        Keys.onLeftPressed: decrementCurrentIndex()
        Keys.onRightPressed: incrementCurrentIndex()
    }
    //<-- slide
}
