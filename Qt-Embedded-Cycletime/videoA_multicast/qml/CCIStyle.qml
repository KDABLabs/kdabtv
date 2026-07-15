pragma Singleton

import QtQuick 2.4

QtObject {
    id: root

    readonly property Colors colors: Colors {
    }

    component Colors: QtObject {
        readonly property color black: "#000000"
        readonly property color grey: "#5A5A5A"
        readonly property color greyDark: "#232323"
        readonly property color greyLight: "#6D6D6D"
        readonly property color red: "#0075c9"
        readonly property color white: "#FFFFFF"
    }
}
