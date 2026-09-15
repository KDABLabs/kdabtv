import QtQuick
import com.kdab.qmlsingleton

Window {
    title: "QML Singleton"
    visible: true
    color: systemPalette.window

    SystemPalette {
        id: systemPalette
    }

    Rectangle {
        id: item
        property color backgroundColor: "#1681F8"
        color: AppSingleton.boundProperty
        width: 300
        height: 300
        x: AppSingleton.margin
        y: AppSingleton.margin

        Image {
            anchors.centerIn: parent
            source: AppSingleton.logo
        }

        Component.onCompleted: {
            AppSingleton.ready = true;
        }

        // Incorrectly bound property
        // AppSingleton.boundProperty: item.backgroundColor

        // Correctly bound property
        Binding {
            target: AppSingleton
            property: "boundProperty"
            value: item.backgroundColor
        }
    }
}
