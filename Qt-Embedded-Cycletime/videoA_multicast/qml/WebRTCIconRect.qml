import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15

import QtQuick.Window 2.1

Rectangle{
    id: root
    width: 300
    height: 80
    color: colors.greyDark
    property alias title: labelTitle.text
    property alias text: labelText.text
    property alias icon: iconImage.source

    signal clicked;

    MouseArea {
        anchors.fill: parent
        onClicked: root.clicked()
    }

    RowLayout {
    anchors.fill: parent
    //spacing: 0

        Image {
            id: iconImage
            Layout.maximumHeight: 80
            Layout.maximumWidth: 80
            Layout.alignment: Qt.AlignLeft
            fillMode: Image.PreserveAspectFit
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.margins: 16

            WebRTCBold {
                id: labelTitle
                text: "Lager 1"
            }
            Label {
                id: labelText
                text: "Lorem ipsum dolor"
                color: colors.white
            }

        }
    }
}
