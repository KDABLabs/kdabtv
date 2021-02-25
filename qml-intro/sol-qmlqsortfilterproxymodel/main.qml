/*************************************************************************
 *
 * Copyright (c) 2016-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.4
import QtQuick.Controls 1.0

Item {
    id: root

    width: 1024
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

                text: qsTr("<b>%1</b> <i>%2</i><br/>%3 seconds")
                        .arg(model.title)
                        .arg(model.producer)
                        .arg(model.duration)
            }
        }
    }

    Row {
        anchors {
            top: parent.top
            left: parent.left
            right: parent.right
        }

        spacing: 5

        ListView {
            width: root.width * 0.25
            height: root.height * 0.75

            spacing: 2

            model: _cppModel

            delegate: delegateComponent
        }

        ListView {
            width: root.width * 0.25
            height: root.height * 0.75

            spacing: 2

            model: _cppFilterProxyModel

            delegate: delegateComponent
        }

        ListView {
            width: root.width * 0.25
            height: root.height * 0.75

            spacing: 2

            model: _cppSortProxyModel

            delegate: delegateComponent
        }
    }

    CheckBox {
        anchors {
            horizontalCenter: parent.horizontalCenter
            bottom: parent.bottom
            bottomMargin: 30
        }

        text: "Show videos only"

        checked: true

        onClicked: {
            _cppFilterProxyModel.videoFilterEnabled = checked;
        }
    }
}
