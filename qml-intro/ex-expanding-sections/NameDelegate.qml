/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Text {
    clip: true
    text: model.name;
    font.pixelSize: 24

    property bool expanded: false

    height: expanded ? implicitHeight : 0

    Behavior on height {
        NumberAnimation { duration:  200 }
    }
}
