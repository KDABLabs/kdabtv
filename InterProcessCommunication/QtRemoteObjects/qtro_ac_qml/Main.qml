import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtRemoteObjects

import Sensors

ApplicationWindow {
    width: 200
    height: 100
    visible: true
    title: qsTr("AC QML")

    SensorsReplica {
        id: sensors
        node: Node {
            registryUrl: "tcp://172.16.224.82:4321"
        }
        onStateChanged: {
            console.log("Sensors replica state changed to " + (sensors.state === 0 ? "Unititialized"
                                                             : sensors.state === 1 ? "Default"
                                                             : sensors.state === 2 ? "Valid"
                                                             : sensors.state === 3 ? "Suspect"
                                                             : sensors.state === 4 ? "SignatureMismatch"
                                                             : "Unknown"))
        }
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 5
        Label {
            text: "Status " + (sensors.status === SensorsReplica.Cooling ? "Cooling" : sensors.status === SensorsReplica.Heating ? "Heating" : "Idle")
        }
        Label {
            text: "Current temperature: " + sensors.currentTemperature
        }
        RowLayout {
            Item  {Layout.fillWidth: true}
            ToolButton {
                text: "-"
                onClicked: {
                    sensors.pushTargetTemperature(sensors.targetTemperature - 0.5)
                }
            }
            Label {
                text: sensors.targetTemperature.toFixed(2)
            }
            ToolButton {
                text: "+"
                onClicked: {
                    sensors.pushTargetTemperature(sensors.targetTemperature + 0.5)
                }
            }
            Item  {Layout.fillWidth: true}
        }
    }
}
