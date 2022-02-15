import QtQuick 2.12
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Page {
    title: settings.user_id === 0 ? "Create User" : "Update User"

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10

        Label {
            text: "Server:Port"
        }
        TextField {
            Layout.fillWidth: true
            id: serverF
            text: settings.server
        }

        Label {
            text: "Nick"
        }
        TextField {
            Layout.fillWidth: true
            id: nickF
            text: settings.nick
        }

        Label {
            text: "Full Name"
        }
        TextField {
            Layout.fillWidth: true
            id: fullnameF
            text: settings.fullname
        }

        Button {
            text: settings.user_id === 0 ? "Create" : "Update"
            onClicked: {
                var nick = nickF.text
                var fullname = fullnameF.text
                var server = serverF.text
                var xhr = new XMLHttpRequest();
                xhr.onreadystatechange = function() {
                    if (xhr.readyState === XMLHttpRequest.DONE) {
                        if (xhr.status === 200) {
                            var json = JSON.parse(xhr.responseText)
                            settings.user_id = json.id
                            settings.nick = nick
                            settings.fullname = fullname
                            settings.server = server

                            stackView.pop()
                        } else {
                            console.error("Error creating/updating user: ", xhr.statusText)
                        }
                    }
                }
                xhr.open(settings.user_id === 0 ? "POST" : "PUT", "http://" + server + "/users");
                xhr.setRequestHeader("Content-Type", "application/json");
                xhr.send(JSON.stringify({
                                            user_id: settings.user_id,
                                            nick: nick,
                                            fullname: fullname,
                                        }));
            }
        }

        Item {
            Layout.fillHeight: true
        }
    }
}
