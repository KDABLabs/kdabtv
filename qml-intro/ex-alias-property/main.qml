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
    width: 400; height: 100; color: "lightblue"

    LineEdit {
        id: lineEdit
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 16
        width: 300; height: 50
        clip: true
    }

    Text {
        anchors.top: lineEdit.bottom
        anchors.topMargin: 12
        anchors.left: parent.left
        anchors.leftMargin: 16
        text: "<b>Summary:</b> " + lineEdit.text
    }

    Image {
        id: clearButton
        source: "../images/clear.svg"
        anchors { right: parent.right; rightMargin: 4
                  verticalCenter: lineEdit.verticalCenter }
        opacity: lineEdit.text === "" ? 0.25 : 1.0
        MouseArea {
            anchors.fill: parent
            onClicked: lineEdit.text = ""
        }
    }
}
