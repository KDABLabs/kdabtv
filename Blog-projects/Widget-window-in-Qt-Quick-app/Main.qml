import QtQuick
import WidgetWindowsInQtQuickApp as Cpp

Window {
    id: frame

    property bool widgetsWindow: false

    function updatePosition(miliseconds: int): void {
        const time = miliseconds / 1000.0;
        const aspectRatio = boundary.right / boundary.bottom * 11
        x = triangleWave(time, boundary.right, aspectRatio);
        y = triangleWave(time, boundary.bottom, 1-aspectRatio);
    }
    function triangleWave(x: double, amplitude: int, period: double): int {
        return Math.abs((2 * amplitude) / Math.PI * Math.asin(Math.sin((2 * Math.PI) / period * x)));
    }
    function toggleWidgetsWindow() {
        frame.widgetsWindow = !frame.widgetsWindow
    }

    flags: Qt.FramelessWindowHint
    color: "transparent"
    visible: false
    width: bounce.width + 1
    height: bounce.height

    QtObject {
        id: boundary
        readonly property int right: Screen.desktopAvailableWidth - frame.width
        readonly property int bottom: Screen.desktopAvailableHeight - frame.height
    }
    Text {
        id: bounce
        text: frame.widgetsWindow ? fontWidgetsForm.text : fontQmlForm.text
        font.pixelSize: 120
        font.family: frame.widgetsWindow ? fontWidgetsForm.fontFamily : fontQmlForm.fontFamily
        color: "#0077C8"
        Rectangle {
            color: "transparent"
            anchors.fill: parent
            border.color: bounce.color
            border.width: 4
        }
    }
    Timer {
        id: timer
        readonly property int startOffset: Math.random() * 36000
        running: true
        triggeredOnStart: true
        repeat: true
        interval: 10
        onTriggered: {
            frame.updatePosition(startOffset + elapsedtimer.deltaTime());
            frame.visible = true;
        }
    }
    Cpp.Timer {
        id: elapsedtimer
    }
    FontControlsQmlForm {
        id: fontQmlForm
        visible: !frame.widgetsWindow
        onToggleWidgetsWindow: () => {
            frame.toggleWidgetsWindow();
        }
    }
    Connections {
        target: fontQmlForm
        function onClosing() {
            Qt.quit();
        }
    }
    Cpp.WidgetFormHandler {
        id: fontWidgetsForm
        visible: frame.widgetsWindow
        onToggleWidgetsWindow: () => {
            frame.toggleWidgetsWindow();
        }
    }
}
