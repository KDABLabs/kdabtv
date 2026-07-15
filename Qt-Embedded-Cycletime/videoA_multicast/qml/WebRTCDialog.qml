import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15 as M
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

import QtQuick.Window 2.1

Dialog {
        id: root
        z:5
        anchors.centerIn: parent
        title: "Modular Dialog"

        modal: true


        onAccepted: console.log("Ok clicked")
        onRejected: console.log("Cancel clicked")

        contentItem:  Item {
            implicitWidth: contentLayout.implicitWidth
            implicitHeight: contentLayout.implicitHeight

            anchors.centerIn: parent
            RowLayout {
                anchors.centerIn: parent

                anchors.bottom: parent.bottom
                anchors.left: parent.left
                anchors.right: parent.right
                WebRTCRedButton {
                    text: "OK"
                    onClicked: root.accept()
                }

                Item{
                    Layout.fillWidth:true
                }

                WebRTCRedButton {
                    text:"Cancel"
                    onClicked: root.reject()
                }
            }
        }

        width: 500
        height: 400


        background: WebRTCTile {
            border.color: colors.kdabBlue

        }
    }
