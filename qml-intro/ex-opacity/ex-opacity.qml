/*************************************************************************
 *
 * Copyright (c) 2017-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
    width: 400; height: 400
    color: "#00a3fc"
//--> slide
    Rectangle {
        x: 50; y: 50; width: 200; height: 300
        color: "white"
        opacity: 0.5

        Rectangle {
            x: 100; y: 25; width: 200; height: 50
            color: "red"
            opacity: 0.5
        }
        Rectangle {
            x: 100; y: 90; width: 200; height: 50
            color: "red"
        }
    }

    Rectangle {
       x: 150; y: 210; width: 200; height: 50
       color: "red"
       opacity: 0.5
    }
    Rectangle {
       x: 150; y: 275; width: 200; height: 50
       color: "red"
    }
//<-- slide
}
