import QtQuick 2.12
import QtQuick.Controls 2.5
import Qt.labs.settings 1.0

ApplicationWindow {
    id: window
    width: 640
    height: 480
    visible: true
    title: qsTr("KDChatApp")

    header: ToolBar {
        contentHeight: toolButton.implicitHeight

        ToolButton {
            id: toolButton
            visible: settings.user_id !== 0
            text: stackView.depth > 1 ? "\u25C0" : "\u2630"
            font.pixelSize: Qt.application.font.pixelSize * 1.6
            onClicked: {
                if (stackView.depth > 1) {
                    stackView.pop()
                } else {
                    drawer.open()
                }
            }
        }

        Label {
            text: "KDChatApp - " + stackView.currentItem.title
            anchors.centerIn: parent
        }
    }

    Settings {
        id: settings
        property int user_id: 0
        property string server
        property string nick
        property string fullname
    }

    Drawer {
        id: drawer
        width: window.width * 0.66
        height: window.height

        Column {
            anchors.fill: parent

            ItemDelegate {
                text: qsTr("Edit User")
                width: parent.width
                enabled: settings.user_id !== 0
                onClicked: {
                    stackView.push("PageUser.qml")
                    drawer.close()
                }
            }
        }
    }

    StackView {
        id: stackView
        initialItem: "PageMessages.qml"
        anchors.fill: parent
    }

    Component.onCompleted: {
        if (settings.user_id === 0) {
            stackView.push("PageUser.qml")
        }
    }
}
