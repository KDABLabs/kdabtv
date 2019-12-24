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
    width: 200; height: 200
    color: "#00a3fc"

    Image {
        x: 50; y: 35
        source: "../images/rocket.png"
        rotation: 45.0
    }
}
