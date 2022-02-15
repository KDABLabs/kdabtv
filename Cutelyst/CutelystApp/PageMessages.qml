import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import QtWebSockets 1.1
import QtQuick.Controls.Material 2.12
import QtQml 2.12

Page {
    title: "Messages"

    ListModel {
        id: messages
    }

    WebSocket {
        id: ws
        url: "ws://" + settings.server + "/ws/" + settings.user_id
        onTextMessageReceived: {
            var json = JSON.parse(message)
            if (Array.isArray(json)) {
                json.forEach(element => messages.append(element))
            } else {
                messages.insert(0, json)
            }
        }
    }

    Timer {
        interval: 2000
        triggeredOnStart: true
        running: settings.user_id !== 0 && ws.status !== WebSocket.Open
        onTriggered: {
            ws.active = false
            ws.active = true
        }
    }

    ColumnLayout {
        anchors.fill: parent

        ScrollView {
            Layout.fillHeight: true
            Layout.fillWidth: true

            ListView {
                width: parent.width
                model: messages
                verticalLayoutDirection: ListView.BottomToTop
                spacing: 5

                delegate: RowLayout {
                    width: ListView.view.width
                    spacing: 0

                    Item {
                        width: 5
                    }

                    Pane {
                        Layout.maximumWidth: parent.width - 10
                        Material.elevation: 6
                        Label {
                            anchors.fill: parent
                            wrapMode: Label.WrapAtWordBoundaryOrAnywhere
                            text: "<b>" + nick + "</b> - " + new Date(created_at).toLocaleString(locale, Locale.ShortFormat) + "<br>" + msg
                        }
                    }
                }
            }

            ScrollBar.horizontal.policy: ScrollBar.AlwaysOff
        }

        ToolBar {
            Layout.fillWidth: true
            enabled: ws.status === WebSocket.Open

            RowLayout {
                anchors.leftMargin: 10
                anchors.fill: parent

                TextField {
                    Layout.fillWidth: true
                    id: messageF
                    onAccepted: postButton.clicked()
                }
                ToolButton {
                    id: postButton
                    enabled: messageF.enabled
                    text: ">"
                    onClicked: {
                        messageF.enabled = false
                        var xhr = new XMLHttpRequest();
                        xhr.onreadystatechange = function() {
                            if (xhr.readyState === XMLHttpRequest.DONE) {
                                messageF.enabled = true
                                if (xhr.status === 200) {
                                    messageF.clear()
                                } else {
                                    console.error("Error posting message: ", xhr.statusText)
                                }
                            }
                        }
                        xhr.open("POST", "http://" + settings.server + "/messages");
                        xhr.setRequestHeader("Content-Type", "application/json");
                        xhr.send(JSON.stringify({
                                                    user_id: settings.user_id,
                                                    msg: messageF.text
                                                }));
                    }
                }
            }
        }
    }
}
