/*************************************************************************
 *
 * Copyright (c) 2017-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

Item {
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        Button {
            // default alignment
            // Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            text: "One"
        }
        Button {
            Layout.alignment: Qt.AlignCenter

            text: "Two"
        }
        Button {
            // Right and Top within this specific cell of the ColumnLayout
            Layout.alignment: Qt.AlignRight | Qt.AlignTop
            text: "Three"
        }
    }
}
