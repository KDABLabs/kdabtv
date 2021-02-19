/*************************************************************************
 *
 * Copyright (c) 2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

ListView {
    width: 300
    height: 200
    model: _myModel
    delegate: Rectangle {
        color: Qt.rgba(0.9,0.9,0.9)
        height: childrenRect.height
        width: parent.width

        Image {
            id: image
            source: model.flag
            width: 64
            height: 64
            fillMode: Image.PreserveAspectFit

            anchors { left:parent.left }
        }
        Text {
            text: model.name + "\n" +"population: " + model.population.toFixed(3) + " mill."
            anchors { left:image.right; verticalCenter: image.verticalCenter; leftMargin: 5 }
        }
        MouseArea {
            anchors.fill: parent
            acceptedButtons: Qt.LeftButton | Qt.RightButton
            onDoubleClicked: {
                if (mouse.button === Qt.LeftButton) {
                    _myModel.duplicateData(model.index);
                } else if (mouse.button === Qt.RightButton) {
                    _myModel.removeData(model.index);
                }
            }
        }
    }
}
