/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Flickable {
    id: flick
    width: 400; height: 400
    contentWidth: 1000
    contentHeight: 1000

    Image {
        width: parent.parent.contentWidth
        height: parent.parent.contentHeight
        source: "../images/rocket.svg"
    }
}
