import QtQuick 2.0

Item {
    id: root
    property alias text: textItem.text
    property alias image: imageItem.source
    // Switch image & text positions
    property bool switchedLayout: false

    width: parent.width
    height: Math.max(imageItem.height, textItem.paintedHeight)

    Image {
        id: imageItem
        x: root.switchedLayout ? 16 : parent.width - width - 10
        y: 8
    }

    Text {
        id: textItem
        width: parent.width - imageItem.width - 40
        x: root.switchedLayout ? parent.width - width - 16 : 16
        y: 8
        color: "#ffffff"
        font.pixelSize: settings.fontS
        wrapMode: Text.WordWrap
    }
}
