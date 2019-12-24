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
    width: 425; height: 200

    Image {
        x: 0; y: 0
        source: "../images/vertical-gradient.png"
    }

    Image {
        x: 225; y: 0
        source: "../images/diagonal-gradient.png"
    }
}
