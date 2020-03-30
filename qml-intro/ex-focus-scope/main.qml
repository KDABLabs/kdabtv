/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    id: window
    color: "white"; width: 400; height: 150

    Column {
        id: column
        anchors.verticalCenter: parent.verticalCenter; spacing: 15
        width: parent.width

        InputField {
            id: firstName
            focus: true
            title: "First Name:"
            KeyNavigation.down: lastName
            anchors { left: parent.left; right: parent.right; leftMargin: 10; rightMargin: 10 }
        }

        InputField {
            id: lastName
            title: "Last Name:"
            KeyNavigation.up: firstName
            anchors { left: parent.left; right: parent.right; leftMargin: 10; rightMargin: 10 }
        }
    }
}
