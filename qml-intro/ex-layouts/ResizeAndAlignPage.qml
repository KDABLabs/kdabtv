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
    width: 400
    height: 300
    //--> slide
    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 5

        RowLayout {
            Layout.alignment: Qt.AlignTop

            Label {
                text: "Filename"
            }

            TextField {
                // stretch to cover the rest of the row layout
                Layout.fillWidth: true
            }
        }

        RowLayout {
            Layout.alignment: Qt.AlignBottom | Qt.AlignRight

            Button {
                text: "Ok"
            }
            Button {
                text: "Cancel"
            }
        }
    }
    //<-- slide
}
