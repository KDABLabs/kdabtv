pragma Singleton

import QtQuick

QtObject {
    property bool ready: false
    property color boundProperty: "black"
    readonly property int margin: ready ? 100 : 0
    readonly property string logo: "kdab.svg"
}
