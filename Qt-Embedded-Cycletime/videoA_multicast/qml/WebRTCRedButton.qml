import QtQuick 2.4
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15 as M

M.Button {
    id: root

    property bool primaryStyle: true

    implicitHeight: 80

    leftPadding: 16
    rightPadding: leftPadding

    padding: 0

    background: Rectangle {
        width: root.width
        height: root.height
        color: colors.kdabBlue
    }

    contentItem: Item {
        implicitWidth: contentLayout.implicitWidth
        implicitHeight: contentLayout.implicitHeight

        anchors.centerIn: parent

        RowLayout {
            id: contentLayout
            anchors.centerIn: parent

          WebRTCBold {
              text: root.text
          }
        }
    }

}
