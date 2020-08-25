import QtQuick 2.0

Item {
    id: root

    property bool isShown: false

    anchors.fill: parent

    QtObject {
        id: priv
        property bool poleOut: false
        // How curly the curtain is when opened
        property int endCurly: 80
        // 0 = pole in, 1 = pole out
        property real polePosition: 0
        property bool showingStarted: false
    }

    function show() {
        priv.showingStarted = true;
        isShown = true;
        hideCurtainAnimation.stop();
        hidePoleAnimation.stop();
        if (priv.poleOut) {
            showCurtainAnimation.restart();
        } else {
            showPoleAnimation.restart();
        }
    }
    function hide() {
        priv.showingStarted = false;
        showCurtainAnimation.stop();
        showPoleAnimation.stop();
        if (priv.poleOut) {
            hideCurtainAnimation.restart();
        } else {
            hidePoleAnimation.restart();
        }
    }

    onIsShownChanged: {
        if (root.isShown) {
            mainView.scheduleUpdate();
        }
    }

    Binding {
        target: mainView
        property: "blurAmount"
        value: 40 * priv.polePosition
        when: root.isShown
    }

    // Pole show/hide animations
    SequentialAnimation {
        id: showPoleAnimation
        NumberAnimation { target: priv; property: "polePosition"; to: 1; duration: 600; easing.type: Easing.InOutQuad }
        PropertyAction { target: priv; property: "poleOut"; value: true }
        ScriptAction { script: showCurtainAnimation.restart(); }
    }
    SequentialAnimation {
        id: hidePoleAnimation
        PropertyAction { target: priv; property: "poleOut"; value: false }
        NumberAnimation { target: priv; property: "polePosition"; to: 0; duration: 600; easing.type: Easing.InOutQuad }
        PropertyAction { target: root; property: "isShown"; value: false }
    }

    // Curtain show/hide animations
    SequentialAnimation {
        id: showCurtainAnimation
        NumberAnimation { target: curtainEffect; property: "rightHeight"; to: root.height-8; duration: 1200; easing.type: Easing.OutBack }
    }
    SequentialAnimation {
        id: hideCurtainAnimation
        NumberAnimation { target: curtainEffect; property: "rightHeight"; to: 0; duration: 600; easing.type: Easing.OutCirc }
        ScriptAction { script: hidePoleAnimation.restart(); }
    }

    MouseArea {
        anchors.fill: parent
        enabled: root.isShown
        onClicked: {
            root.hide();
        }
    }

    BorderImage {
        anchors.right: parent.right
        anchors.top: parent.top
        border.left: 22
        border.right: 64
        border.top: 0
        border.bottom: 0
        width: 86 + priv.polePosition * (viewItem.width-88)
        z: 20
        source: "images/info.png"
        opacity: 0.5 + priv.polePosition
        MouseArea {
            anchors.fill: parent
            anchors.margins: -20
            onClicked: {
                if (priv.showingStarted) {
                    root.hide();
                } else {
                    root.show();
                }
            }
        }
    }

    Item {
        id: viewItem
        anchors.right: parent.right
        width: Math.min(620, parent.width)
        height: parent.height + priv.endCurly - 16
        y: 8
        visible: isShown

        Rectangle {
            id: backgroundItem
            anchors.fill: parent
            anchors.margins: 16
            anchors.topMargin: 8
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#101010" }
                GradientStop { position: 0.3; color: "#404040" }
                GradientStop { position: 1.0; color: "#090909" }
            }
            border.color: "#808080"
            border.width: 1
            opacity: 0.8
        }

        Flickable {
            id: flickableArea
            anchors.fill: backgroundItem
            contentHeight: infoTextColumn.height + 32
            contentWidth: backgroundItem.width
            flickableDirection: Flickable.VerticalFlick
            clip: true

            Column {
                id: infoTextColumn
                width: parent.width
                spacing: 32

                Text {
                    id: textItem
                    x: 32
                    height: 60
                    color: "#ffffff"
                    font.pixelSize: settings.fontMM
                    text: "<i>The Cinematic Experience</i>"
                    verticalAlignment: Text.AlignBottom
                }

                InfoViewItem {
                    text: "Welcome to <i>'Cinematic Experience'</i> demo. This application demonstrates the power of Qt5 and few of the new additions available in QtQuick 2.0. Below is a short summary of those new features which have been used in this demo application."
                    image: "images/qt_logo2.png"
                }
                InfoViewItem {
                    text: "<b>Rendering</b><br/>Qt5 has brand new rendering backend 'QML SceneGraph' which is optimized for hardware accelerated rendering. This allows to take full gains out of OpenGL powered GPUs on desktop and embedded devices. Not just performance, new Qt5 rendering backend also allows features which have not been possible earlier."
                }
                InfoViewItem {
                    text: "<b>Particles</b><br/>Qt5 comes with a fresh particles plugin 'QtQuick.Particles 2.0' which is superior compared to Qt4 particles. In this demo application, twinkling stars, shooting star and fog/smoke have been implemented using this new particles engine. Superb."
                    image: "images/sc2.png"
                }
                InfoViewItem {
                    text: "<b>Sprites</b><br/>QtQuick 2.0 has built-in support for sprites using Sprite, SpriteSequence and AnimatedSprite elements. Sprites can also be used as a source for particles. In this demo application, shooting star is an AnimatedSprite with 16 frames."
                    image: "images/sc5.png"
                    switchedLayout: true
                }
                InfoViewItem {
                    text: "<b>Animations</b><br/>QtQuick has always had a very strong animations support. Qt5 supports now also animations along a non-linear paths using PathAnimation and PathInterpolator QML elements. In this demo, shooting star position moves along PathAnimation using PathCurves."
                    image: "images/sc1.png"
                }
                InfoViewItem {
                    text: "<b>ShaderEffects</b><br/>Qt5 supports ShaderEffect and ShaderEffectSource QML elements which allow writing custom GLSL shader effects. This gives developers a lot of control to transform and enhance QML UIs by increasing dynamicity. In this demo, custom shader effect is used for lighting the movie delegates."
                    image: "images/sc3.png"
                    switchedLayout: true
                }
                InfoViewItem {
                    text: "<b>Graphical Effects</b><br/>Qt5 comes with pre-defined set of effects such as drop-shadow, blur, glow, colorize etc. These are available in 'QtGraphicalEffects 1.0' plugin. In this demo, DropShadow is used to improve the appearance of movie title texts."
                    image: "images/sc4.png"
                }

                Row {
                    anchors.horizontalCenter: parent.horizontalCenter
                    height: 128
                    spacing: 16
                    Image {
                        source: "images/qt_ambassador_logo.png"
                        anchors.bottom: parent.bottom
                    }
                    Image {
                        source: "images/cc-by_logo.png"
                        anchors.bottom: parent.bottom
                    }
                    Image {
                        source: "images/quit_logo.png"
                        anchors.bottom: parent.bottom
                    }
                }
                Text {
                    anchors.horizontalCenter: parent.horizontalCenter
                    horizontalAlignment: Text.AlignHCenter
                    color: "#909090"
                    font.pixelSize: settings.fontXS
                    text: "Copyright 2012 QUIt Coding. Reuse sources freely."
                }
            }
        }

        // Grip to close the view by flicking
        Image {
            id: gripImage
            anchors.right: parent.right
            anchors.rightMargin: 8
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 8
            source: "images/grip.png"
            opacity: 0.25
            MouseArea {
                property int pressedY: 0
                anchors.right: parent.right
                anchors.bottom: parent.bottom
                anchors.bottomMargin: priv.endCurly - 16
                anchors.margins: -16
                width: 90
                height: 80
                onPressed: {
                    showCurtainAnimation.stop();
                    hideCurtainAnimation.stop();
                    pressedY = mouseY
                }
                onPositionChanged: {
                    curtainEffect.rightHeight = root.height - (pressedY - mouseY) - 8
                }
                onReleased: {
                    if (mouseY < -root.height*0.2) {
                        root.hide();
                    } else {
                        root.show();
                    }
                }
            }
        }
    }

    CurtainEffect {
        id: curtainEffect
        anchors.fill: viewItem
        source: ShaderEffectSource { sourceItem: viewItem; hideSource: true }
        rightHeight: 0
        leftHeight: rightHeight
        Behavior on leftHeight {
            SpringAnimation { spring: .4; damping: .05; mass: .5 }
        }
        // Hide smoothly when curtain closes
        opacity: 0.004 * rightHeight
    }
}
