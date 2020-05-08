/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Item {
    id: root
    width: 1024; height: 768

    property var easingTypes: [
        "Linear", "InQuad", "OutQuad", "InOutQuad", "OutInQuad",
        "InCubic", "OutCubic", "InOutCubic", "OutInCubic", "InQuart",
        "OutQuart", "InOutQuart", "OutInQuart",  "InQuint", "OutQuint",
        "InOutQuint", "OutInQuint", "InSine", "OutSine", "InOutSine",
        "OutInSine", "InExpo", "OutExpo", "InOutExpo", "OutInExpo",
        "InCirc", "OutCirc", "InOutCirc", "OutInCirc", "InElastic",
        "OutElastic", "InOutElastic", "OutInElastic", "InBack", "OutBack",
        "InOutBack", "OutInBack", "InBounce", "OutBounce", "InOutBounce",
        "OutInBounce"
    ]

    Grid {
        id: container
        anchors.top: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.margins: 10
        columns: 7
        spacing: 10
        Repeater {
            model: easingTypes
            EasingCurve {
                text: modelData
                source: "../images/" + modelData + ".png"
                onClicked: {
                    anim.easing.type = modelData
                    anim.restart()
                }
            }
        }
    }

    Rectangle {
        id: path
        width: parent.width
        height: 70
        anchors.bottom: parent.bottom
        gradient: Gradient{
            GradientStop { position: 0.0; color: "white" }
            GradientStop { position: 0.4; color: "lightsteelblue" }
            GradientStop { position: 1.0; color: "blue" }
        }
    }

    Rectangle {
        id: square
        width: 50; height: 50
        color: "blue"
        border.color: "lightsteelblue"
        border.width: 1
        radius: 8
        anchors.bottom: parent.bottom
        NumberAnimation on x {
            id: anim
            from: 50; to: root.width - 100
            duration: 2500
        }
    }
}
