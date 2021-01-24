/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Item {
    width: 500
    height: 500

    Text {
        anchors {
            top: parent.top
            right: parent.right
            margins: 5
        }

        text: _userData.loggedIn ? "Logout" : "Login"

        MouseArea {
            anchors.fill: parent
            onClicked: _userData.loggedIn = !_userData.loggedIn
            cursorShape: Qt.PointingHandCursor
        }
    }

    Rectangle {
        visible: _userData.loggedIn
        anchors.centerIn: parent
        width: col.width + 50
        height: col.height +50
        border {
            color: "black"
            width: 2
        }
        radius: 10



        Column {
            id: col
            spacing: 3
            anchors.centerIn: parent
            Text { text: "<b>Details</b>" }
            Text { text: "Name: " + _userData.name }
            Text { text: "Age: " + _userData.age }
            Text { text: "Role: " + role()}
        }
    }

    function role() {
        if ( _userData.role === 0 ) // Developer
            return "Developer"
        else if ( _userData.role === 1 ) // Tester
            return "Tester"
        else
            return "Project Manager"
        // Note: we will see how to use reference enum keys instead of their
        // integer value later
    }
}
