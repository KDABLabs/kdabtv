import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import QtQuick.Window 2.1

WebRTCTile {
            id: rect2

            ListModel {
                id: icons
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 0}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 1}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 2}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 3}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 4}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 5}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 6}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 7}
            ListElement { icon: "qrc:///kdab_logo_square.png"; gridId: 8}
            }

            GridView {
                   id: grid
                   interactive: false
                   anchors.fill: parent
                   topMargin: 60
                   bottomMargin: 60
                   leftMargin: 60
                   rightMargin: 60

                   cellWidth: 80
                   cellHeight: 80
                   model: icons

                   delegate: WebRTCSortTile {
                   }
               }

            MouseArea {
                property int currentId: -1 // Original position in model
                property int newIndex // Current Position in model
                property int index: grid.indexAt(mouseX, mouseY) // Item underneath cursor

                id: loc
                anchors.fill: parent
                onPressAndHold: currentId = icons.get(newIndex = index).gridId
                onReleased: currentId = -1
                onPositionChanged: {
                    if (loc !== currentId && index !== -1 && index !== newIndex)
                        icons.move(newIndex, newIndex = index, 1)
                }
            }
        }
