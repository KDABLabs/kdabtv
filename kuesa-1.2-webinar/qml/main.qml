import QtQuick 2.15
import QtQuick.Scene3D 2.15

Item {
    id: mainRoot

    // 3D View
    Scene3D {
        anchors.fill: parent
        multisample: true
        aspects: ["input", "logic", "render", "animation"]

        // Renders our Kuesa Scene
        KuesaSceneStep4 {
            id: kuesaScene
            sceneWidth: mainRoot.width
            sceneHeight: mainRoot.height
        }

        focus: true
        Keys.onSpacePressed: kuesaScene.animated = !kuesaScene.animated
    }

    Text {
        id: innerText

        // Bind position and opacity to motorLabelScreenPosition and motorLabelOpacity
        readonly property vector2d position: kuesaScene.motorLabelScreenPosition
        x: position.x - implicitWidth * 0.5
        y: position.y - implicitHeight * 0.5
        opacity: 0.5 * kuesaScene.motorLabelOpacity

        font.bold: true

        color: "white"
        text: "Overheating"
        style: Text.Sunken
        styleColor: "red"

        // Animate the size of the text
        NumberAnimation on scale {
            from: 2; to: 4
            duration: 700
            easing.type: Easing.InOutCubic
            loops: Animation.Infinite
        }
    }
}
