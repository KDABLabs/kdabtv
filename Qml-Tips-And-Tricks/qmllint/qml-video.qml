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
            text: showIcons ? "Hide icons" : "Show icons"
            onClicked: showIcons = !showIcons
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

                text: model.name
                checked: ListView.view.currentIndex === index
                icon.source: showIcons ? Qt.resolvedUrl("kdab.png") : ""

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





