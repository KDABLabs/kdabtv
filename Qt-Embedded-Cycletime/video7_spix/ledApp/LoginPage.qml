import QtQuick 2.15
import QtQuick.Controls 2.0 as QQC2
import QtQuick.Layouts 1.3


Rectangle {
    id: root

    width:200
    height: 200

    anchors.centerIn: parent
    color: "lightgrey"
    opacity: 0.58

    signal login();

    ColumnLayout {
        width:500
        height: 500

        anchors.centerIn: parent

        RowLayout {
            id: userRow

            QQC2.Label{
                text: qsTr("Username: ")
            }

            QQC2.TextField {
                id: userField
                placeholderText: "user"
                function wipe() {
                    userField.clear()
                }

            }
        }

        RowLayout {
            id: passwordRow

            QQC2.Label{
                text: qsTr("Password: ")
            }

            QQC2.TextField {
                id: passwordField
                echoMode: TextInput.Password
                placeholderText: "*****"

            }
        }

        QQC2.Button {
            id: loginButton
            text: qsTr("Login")
            onClicked:
                if(userField.text === "christoph" && passwordField.text === "secret") {
                    console.log("login successful");
                    root.login();
                }
        }
    }
}
