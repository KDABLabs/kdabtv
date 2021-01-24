/*************************************************************************
 *
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0
import CustomComponents 1.0

Rectangle {
    width: 500
    height: 360

    Text {
        text: timer.active ? qsTr( "Timer is running. Tap to stop." )
                           : qsTr( "Timer is stopped. Tap to start." )
        font.pixelSize: 24
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 60
    }

    RandomTimer {
        id: timer
        interval: timer.randomInterval( 500, 1500 )

        onTimeout: {
            console.log( "Timer fired!" );
            beepAnimation.running = true;
        }
    }

    MouseArea {
        anchors.fill: parent

        onClicked: {
            if ( timer.active === false ) {
                console.log( "Starting timer" );
                timer.start();
            } else {
                console.log( "Stopping timer" );
                timer.stop();
            }
        }
    }

    Image {
        id: roadrunner
        source: "Roadrunner.gif"
    }

    Text {
        id: beepText
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: parent.top
        anchors.topMargin: 40
        text: "MEEP! MEEP!"
        font.pixelSize: 40
        color: "red"
        opacity: 0.0
    }

    SequentialAnimation {
        id: beepAnimation
        running: false

        PropertyAnimation {
            target: beepText
            property: "opacity"
            duration: 50
            from: 0.0
            to: 1.0
        }

        PropertyAnimation {
            target: beepText
            property: "opacity"
            duration: 300
            from: 1.0
            to: 0.0
        }
    }
}
