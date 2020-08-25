import QtQuick 2.0

Item {
    property real rating: 5.0

    width: emptyRatingStarsImage.width + ratingTextItem.paintedWidth + 4
    height: 32

    // TODO: Implement ratings in shader + animations, instead of clipping trick
    Image {
        id: emptyRatingStarsImage
        source: "images/stars2.png"
    }
    Item {
        id: ratingImageItem
        height: 32
        width: (36 * rating) - 2
        clip: true
        Image {
            source: "images/stars.png"
        }
    }
    Text {
        id: ratingTextItem
        anchors.left: emptyRatingStarsImage.right
        anchors.leftMargin: 4
        anchors.verticalCenter: ratingImageItem.verticalCenter
        color: "#ffffff"
        font.pixelSize: settings.fontM
        text: "(" + rating.toFixed(1) + ")"
    }
}
