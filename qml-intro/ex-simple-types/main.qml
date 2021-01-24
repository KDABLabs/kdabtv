/*************************************************************************
 *
 * Copyright (c) 2015-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

//--> slide
import QtQuick 2.0
Item {
    width: _aSize.width
    height: _aSize.height

    Column {
        //--> hide
        anchors.centerIn: parent
        spacing: 10
        //<-- hide
        Text { text: "The string: " + _aString }
        Text { text: "The size: " + _aSize }
        Text { text: "Today is: " + _today }
    }
}
//<-- slide
