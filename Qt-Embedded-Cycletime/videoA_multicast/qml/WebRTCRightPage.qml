import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

import QtQuick.Window 2.1

Item {
    id: root

    signal dialogueRequested

    GridLayout {
        anchors.fill: parent

        rows: 2
        columns: 3

        rowSpacing: 0
        columnSpacing: 0

        WebRTCTile {
            Layout.columnSpan: 2
            Layout.rowSpan: 2

            Layout.minimumWidth: 800

            Image {
                anchors.fill: parent
                fillMode: Image.PreserveAspectFit
                source: "qrc:///parts.svg"
            }

        }

        WebRTCTile {
            ColumnLayout {
                anchors.fill: parent
                WebRTCRedButton{
                    Layout.alignment: Qt.AlignHCenter
                    text: "Something"}
                WebRTCRedButton{
                    Layout.alignment: Qt.AlignHCenter
                    text: "Launch Dialogue"
                    onClicked: {root.dialogueRequested()}}
                WebRTCRedButton{
                    Layout.alignment: Qt.AlignHCenter
                    text: "Somethingelse"}
            }
        }

        WebRTCTile {
            ColumnLayout {

                anchors.centerIn: parent


                WebRTCLabel {
                    text: "9%"
                }

                WebRTCSlider {

                }

            }
        }
    }
}
