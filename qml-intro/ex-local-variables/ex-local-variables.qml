/*************************************************************************
 *
 * Copyright (c) 2011-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

//--> slide
Rectangle {
    id: root
    width: cellCount * itemSize
    height: cellCount * itemSize
    border.color: "black"

    property int cellCount: 4
    property int itemSize: 80

    Rectangle {
        property int __row: 2
        property int __col: 1

        color: "blue"
        x: __col * root.itemSize
        y: __row * root.itemSize
        width: root.itemSize
        height: root.itemSize
        //--> hide
        focus: true
        Keys.onLeftPressed: __col = (__col +root.cellCount-1) % root.cellCount
        Keys.onRightPressed: __col = (__col +1) % root.cellCount
        Keys.onDownPressed: __row = (__row +1) % root.cellCount
        Keys.onUpPressed: __row = (__row +root.cellCount-1) % root.cellCount
        //<-- hide
    }
}
//<-- slide
