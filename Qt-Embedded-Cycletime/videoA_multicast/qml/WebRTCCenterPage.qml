import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

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
            ColumnLayout {
                anchors.centerIn: parent

                WebRTCLabel{
                    font.pixelSize: 30
                    text: "Qt <br> Streamed <br> to the Browser"
                    horizontalAlignment: Qt.AlignHCenter
                }
            }
        }

        WebRTCTile {
            id: rect2
            WebRTCLabel{
                id: techTownLetters
                anchors.centerIn: parent
                font.pixelSize: 30
                property string originalText: "EWN { 2026 Nürnberg }";
                property int lettersShown: 20;
                text: originalText.substring(0, lettersShown) ;
                SequentialAnimation{
                    running: true
                    loops: Animation.Infinite
                    NumberAnimation{
                        target: techTownLetters
                        property: "lettersShown"
                        from: 3
                        to: 21
                        easing.type: Easing.InQuad
                        duration: 3500
                    }
                    NumberAnimation{
                        target: techTownLetters
                        property: "lettersShown"
                        from: 20
                        to: 1
                        duration: 500
                    }
                }

            }
        }

        WebRTCTile {
            id: rect3

            ListView {
                anchors.fill: parent
                anchors.topMargin: 20
                anchors.bottomMargin: 20
                anchors.leftMargin: 40
                anchors.rightMargin: 40
                spacing: 10
                model: [
                    {"skill":"Qt", "image":"qrc:/kdab_skills/kdab_qt.png", "description": "Qt & QML Services"},
                    {"skill":"C++", "image":"qrc:/kdab_skills/kdab_cpp.png", "description": "Qt & QML Services"},
                    {"skill":"Rust", "image":"qrc:/kdab_skills/kdab_rust.png", "description": "Qt & QML Services"},
                    {"skill":"Embedded", "image":"qrc:/kdab_skills/kdab_os.png", "description": "Qt & QML Services"},
                    {"skill":"Slint", "image":"qrc:/kdab_skills/kdab_slint.png", "description": "Qt & QML Services"},
                    {"skill":"3D", "image":"qrc:/kdab_skills/kdab_3d.png", "description": "Qt & QML Services"},
                    {"skill":"Flutter", "image":"qrc:/kdab_skills/kdab_flutter.png", "description": "Qt & QML Services"},
                ]
                delegate: WebRTCIconRect {
                    title: modelData.skill
                    text: modelData.description
                    icon: modelData.image
                }
            }
        }

        WebRTCTile {
            id: rect4

            ColumnLayout {

                anchors.centerIn: parent


                WebRTCLabel {
                    text: Math.floor(slider.value * 100) +  " %"
                }

                WebRTCSlider {
                    id: slider
                    value: 0.2
                }

            }
        }

        WebRTCTile {
            id: rect5

            ColumnLayout {
                anchors.centerIn: parent
                WebRTCLabel{
                    font.pixelSize: 30
                    text: "<b>Qt</b> <br> -> gstreamer <br> -> WebRTC"
                    horizontalAlignment: Qt.AlignLeft
                }
            }

        }

        WebRTCTile {
            id: rect6

            Image {
                anchors.margins: 30
                anchors.bottom: parent.bottom
                anchors.right: parent.right
                source: "qrc:///demo_logos.png"
            }

        }
    }
}
