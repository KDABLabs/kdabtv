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
    width: 200; height: 200

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
                id: delegateImage
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
    GridView {
        anchors.fill: parent
        model: nameModel
        delegate: nameDelegate
        clip: true
    }
    //<-- slide
}
