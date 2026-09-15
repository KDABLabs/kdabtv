import QtQuick 2.15
import QtQuick.Controls 2.15

import com.kdab.sharedqtquicksingletondemo

Rectangle {
    width: 100
    color: MyNonDefaultConstructibleSingleton.sharedColor ?? "green"
    onColorChanged: {
        console.log(this.color);
    }
    Column {
        anchors.centerIn: parent
        z: 1
        Button {
            text: "Gray"
            onPressed: {
                MyNonDefaultConstructibleSingleton.sharedColor = text;
            }
        }
        Button {
            text: "Steelblue"
            onPressed: {
                MyNonDefaultConstructibleSingleton.setSharedColor(text);
            }
        }
    }
    Text {
        color: "white"
        anchors.fill: parent
        anchors.margins: 8
        text: "KDAB ipsum Nuno sit amet consectetur adipiscing elit. Quisque faucibus ex sapien vitae pellentesque sem placerat. In id cursus mi pretium tellus duis convallis. Tempus leo eu aenean sed diam urna tempor. Pulvinar vivamus fringilla lacus nec metus bibendum egestas. Iaculis massa nisl malesuada lacinia integer nunc posuere. Ut hendrerit semper vel class aptent taciti sociosqu. Ad litora torquent per conubia nostra inceptos himenaeos."
        wrapMode: Text.WordWrap
    }
}
