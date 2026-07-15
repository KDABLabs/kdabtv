import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15
//import QtCharts 2.15

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
            Layout.column: 1
            Layout.row: 1


            Column {
                    anchors.centerIn: parent

                    WebRTCRadioButton {
                    }
                    WebRTCRadioButton {
                        text: qsTr("Medium")
                        checked: true
                    }
                    WebRTCRadioButton {
                        text: qsTr("Large")
                    }
                }
        }

        WebRTCTile {
            Layout.column: 1
            Layout.row: 2

            ColumnLayout {
                anchors.centerIn: parent

                WebRTCLabel{
                    text: "Couldnt read this"
                }

                TextArea {
                    Layout.alignment: Qt.AlignHCenter
                    text: "Changeme"
                }

                WebRTCRedButton {
                    Layout.alignment: Qt.AlignHCenter
                    text: "SendMessage"
                }
            }
        }


        WebRTCTile {
            Layout.column: 2
            Layout.row: 1

            Layout.columnSpan: 2
            Layout.rowSpan: 2

            Image {
                anchors.fill: parent
                source: "qrc:///nuremberg.jpg"
                anchors.margins: 32
                fillMode: Image.PreserveAspectFit
            }

            Layout.minimumWidth: 800

        }
    }
}
