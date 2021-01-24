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
    width: 500
    height: 500

    Column {
        anchors {
            fill: parent
            margins: 5
        }

        spacing: 3

        Repeater {
            id: repeater

            // clicking the mouse area will destroy and recreate all delegates
            model: mouseArea.pressed ? 0 : _userList.count

            delegate: Rectangle {
                width: parent.width
                height: 40
                color: "lightblue"

                Text {
                    // here the invokable method is called
                    text: _userList.userAt(model.index).name
                }
            }
        }
    }

    MouseArea {
        id: mouseArea

        anchors.fill: parent

        onPressed: {
            // trigger garbage collector to clean up all unused JavaScript objects
            gc();
        }
    }
}
