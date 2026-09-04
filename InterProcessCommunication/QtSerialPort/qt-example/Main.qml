pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root

    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    readonly property int fontPixelSize: 24
    // property real velo: 0.0
    // property real voltage: 0.0

    // PropertyAnimation {
    //     target: root
    //     property: "velo"
    //     from: 0.0
    //     to: 1.0
    //     duration: 10000
    //     running: true
    //     loops: -1
    // }

    Connections {
        target: CommandInterface
        function onSpeedChanged() {
            canvas.requestPaint()
        }
    }

    ColumnLayout {
        anchors.centerIn: parent

        Label {
            text: "%1 rad/s".arg(CommandInterface.speed.toFixed(2))
            Layout.alignment: Layout.Center
            font.pixelSize: root.fontPixelSize
        }

        Rectangle {
            Layout.preferredHeight: 100
            Layout.preferredWidth: 200
            Layout.alignment: Layout.Center

            Canvas {
                id: canvas

                anchors.fill: parent

                onPaint: {
                    let ctx = canvas.getContext('2d')
                    let theta = Math.PI * (1 - (CommandInterface.speed / 5.0))

                    ctx.clearRect(0, 0, canvas.width, canvas.height)

                    ctx.lineWidth = 1
                    ctx.strokeStyle = Qt.rgba(0, 0, 0, 1)

                    ctx.beginPath()

                    ctx.arc(canvas.width / 2, canvas.height, canvas.width / 2, 0, Math.PI, true)

                    ctx.stroke()

                    ctx.strokeStyle = Qt.rgba(1, 0, 0, 1)

                    ctx.beginPath()

                    ctx.moveTo(canvas.width / 2, canvas.height)

                    ctx.lineTo(
                        (canvas.width / 2) + ((canvas.width / 3) * Math.cos(theta)),
                        (canvas.height) - ((canvas.width / 3) * Math.sin(theta))
                    )

                    ctx.stroke()
                }
            }
        }

        RowLayout {
            Button {
                text: "⬅"
                font.pixelSize: root.fontPixelSize
                onClicked: CommandInterface.decreaseVoltage()
            }

            Label {
                text: "%1 V".arg(CommandInterface.voltage)
                font.pixelSize: root.fontPixelSize
            }

            Button {
                text: "➡"
                font.pixelSize: root.fontPixelSize
                onClicked: CommandInterface.increaseVoltage()
            }
        }
    }
}
