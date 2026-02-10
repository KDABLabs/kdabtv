pragma ComponentBehavior: Bound

import QtQuick
import QtQuick.Layouts
import QtQuick.Controls

Window {
    id: root
    visible: true

    height: 300

    property bool showIcons: true

    ColumnLayout {
        anchors.fill: parent

        Button {
            property var showIcons: false

            text: root.showIcons ? "Hide icons" : "Show icons"
            onClicked: root.showIcons = !root.showIcons
        }

        ListView {
            id: list

            Layout.fillWidth: true
            Layout.fillHeight: true

            model: ListModel {
                id: nameModel
                ListElement { name: "James Holden" }
                ListElement { name: "Naomi Nagata" }
                ListElement { name: "Amos Burton" }
            }

            delegate: CheckDelegate {

                required property string name
                required property int index

                text: name
                checked: ListView.view.currentIndex === index
                icon.source: root.showIcons ? Qt.resolvedUrl("kdab.png") : ""

                icon.width: 50
                icon.height: 50

                width: ListView.view.width

                onClicked: {
                    list.currentIndex = index
                }
            }
        }
    }
}





