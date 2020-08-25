import QtQuick 2.0

Item {
    id: root

    property bool isShown: false

    anchors.fill: parent

    function show() {
        isShown = true;
        hideAnimation.stop();
        showAnimation.restart();
    }
    function hide() {
        isShown = false;
        showAnimation.stop();
        hideAnimation.restart();
    }

    SequentialAnimation {
        id: showAnimation
        PropertyAction { target: backgroundItem; property: "visible"; value: true }
        ParallelAnimation {
            NumberAnimation { target: backgroundItem; property: "opacity"; to: 1; duration: 250; easing.type: Easing.InOutQuad }
            NumberAnimation { target: backgroundItem; property: "scale"; to: 1; duration: 500; easing.type: Easing.OutBack }
        }
    }
    SequentialAnimation {
        id: hideAnimation
        ParallelAnimation {
            NumberAnimation { target: backgroundItem; property: "opacity"; to: 0; duration: 500; easing.type: Easing.InOutQuad }
            NumberAnimation { target: backgroundItem; property: "scale"; to: 0.6; duration: 500; easing.type: Easing.InOutQuad }
        }
        PropertyAction { target: backgroundItem; property: "visible"; value: false }
    }

    MouseArea {
        anchors.fill: parent
        enabled: root.isShown
        onClicked: {
            root.hide();
        }
    }

    Image {
        id: settingsIcon
        anchors.left: parent.left
        anchors.leftMargin: 4
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 4
        source: "images/settings.png"
        opacity: backgroundItem.opacity + 0.4
        MouseArea {
            anchors.fill: parent
            anchors.margins: -20
            onClicked: {
                if (root.isShown) {
                    root.hide();
                } else {
                    root.show();
                }
            }
        }
    }

    BorderImage {
        id: backgroundItem
        anchors.left: settingsIcon.horizontalCenter
        anchors.bottom: settingsIcon.verticalCenter
        width: Math.min(480, parent.width - 60)
        height: settingsContentColumn.height + 36
        source: "images/panel_bg.png"
        border.left : 22
        border.right : 10
        border.top : 5
        border.bottom : 26

        transformOrigin: Item.BottomLeft
        visible: false
        opacity: 0
        scale: 0.6

        Column {
            id: settingsContentColumn
            width: parent.width
            y: 8
            Switch {
                text: "Show movies cover lighting?"
                checked: settings.showLighting
                onCheckedChanged: {
                    settings.showLighting = checked;
                }
            }
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 32
                height: 1
                color: "#404040"
            }
            Switch {
                text: "Show shooting star particles?"
                checked: settings.showShootingStarParticles
                onCheckedChanged: {
                    settings.showShootingStarParticles = checked;
                }
            }
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 32
                height: 1
                color: "#404040"
            }
            Switch {
                text: "Show fog particles?"
                checked: settings.showFogParticles
                onCheckedChanged: {
                    settings.showFogParticles = checked;
                }
            }
            Rectangle {
                anchors.horizontalCenter: parent.horizontalCenter
                width: parent.width - 32
                height: 1
                color: "#404040"
            }
            Switch {
                text: "Do you l-o-v-e colors?"
                checked: settings.showColors
                onText: "Yes"
                offText: "No!"
                onCheckedChanged: {
                    settings.showColors = checked;
                }
            }
        }
    }
}
