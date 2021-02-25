/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.4

Item {
    width: 800
    height: 500

    Component {
        id: delegateComponent

        Rectangle {
            width: ListView.view.width
            height: 40

            color: model.mediaType === "audio" ? "lightgreen" : "lightblue"

            Text {
                anchors {
                    fill: parent
                    margins: 5
                }

                text: qsTr("<b>%1</b> <i>%2</i> - %3 seconds")
                        .arg(model.title)
                        .arg(model.producer)
                        .arg(model.duration)
            }
        }
    }

    ListView {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.horizontalCenter
            rightMargin: 5
            bottom: parent.bottom
        }

        spacing: 2

        model: _cppModel

        delegate: delegateComponent
    }

    ListView {
        anchors {
            top: parent.top
            left: parent.horizontalCenter
            leftMargin: 5
            right: parent.right
            bottom: parent.bottom
        }

        spacing: 2

        model: _cppProxyModel

        delegate: delegateComponent
    }
}
