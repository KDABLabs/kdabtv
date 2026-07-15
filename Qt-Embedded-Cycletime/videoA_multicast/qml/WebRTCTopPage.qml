import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia
import QtWebView 1.15

import QtQuick.Window 2.1

Item {
    id: page1
    GridLayout {
        anchors.fill: parent

        rows: 2
        columns: 3

        rowSpacing: 0
        columnSpacing: 0

        WebRTCTile {
            id: rect1

            Layout.column: 1
            Layout.row: 1

            ColumnLayout {
                height: 250
                anchors.bottom: parent.bottom
                anchors.horizontalCenter: parent.horizontalCenter

                WebRTCIconRect {
                    title: "Lager1"
                    text: "Lorem ipsum dolor"
                }
                WebRTCIconRect {
                    title: "Lager2"
                    text: "Lorem ipsum dolor"
                }
            }

        }
        WebRTCTile {
            id: rect6

            Layout.column: 1
            Layout.row: 2

            ColumnLayout {
                height: 250
                anchors.top: parent.top
                anchors.horizontalCenter: parent.horizontalCenter

                WebRTCIconRect {
                    title: "Lager1"
                    text: "Lorem ipsum dolor"
                }
                WebRTCIconRect {
                    title: "Lager2"
                    text: "Lorem ipsum dolor"
                }
            }
        }


        WebRTCTile {
        Layout.column: 2
        Layout.row: 1

        Layout.columnSpan: 2
        Layout.rowSpan: 2

        Layout.minimumWidth: 800

            MediaPlayer {
                id: mediaplayer2
                autoPlay: true
                source: "./cci.m4v"
                onErrorOccurred: (error, errorString) => {
                        console.log("MediaPlayer Error: " + errorString)
                }
                videoOutput: videoOutput2
            }

            VideoOutput {
                id: videoOutput2
                anchors.fill: parent
            }

        }
    }
}

