import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia

import QtQuick.Window 2.1

Item {
    id: page1
    GridLayout {
        anchors.fill: parent

        rows: 2
        columns: 3

        rowSpacing: 0
        columnSpacing: 0


        WebRTCGridTile {
            Layout.column: 1
            Layout.row: 1

        }

        WebRTCTile {
            Layout.column: 1
            Layout.row: 2

            Image {
                Layout.maximumHeight: 200
                Layout.maximumWidth: 200
                Layout.alignment: Qt.AlignHCenter | Qt.AlignVCenter
                source: "qrc:///kdab_logo_square.png"
                fillMode: Image.PreserveAspectFit
            }

        }

        WebRTCTile {
            Layout.column: 2
            Layout.row: 1

            Layout.columnSpan: 2
            Layout.rowSpan: 2

            Layout.minimumWidth: 800


            // MediaPlayer {
            //     id: mediaplayer2
            //     autoPlay:  true
            //     source: "file:///home/christoph/Video/cci.m4v"
            //     onHasVideoChanged: console.log("CHRISTOPH GOT VIDEO")
            //     videoOutput: videoOutput2
            // }

            // VideoOutput {
            //     id: videoOutput2
            //     anchors.fill: parent
            // }
        }
    }
}
