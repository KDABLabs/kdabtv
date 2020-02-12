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
    width: 400; height: 400; color: "black"

    Image {
        id: rocket
        x: 150; y: 150
        source: "../images/rocket.svg"
        transformOrigin: Item.Center
    }
//--> slide
    Keys.onPressed: {
        if (event.key === Qt.Key_Left)
            rocket.rotation = (rocket.rotation - 10) % 360;
        else if (event.key === Qt.Key_Right)
            rocket.rotation = (rocket.rotation + 10) % 360;
    }
//<-- slide
    focus: true
}
