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
    width: 600
    height: 400
    //--> slide
    GridLayout {
        anchors.fill: parent
        anchors.margins: 5

        columns: 3

        // auto positioning based on flow: forth button overflows into second row//--> hide
        Button {
            Layout.fillWidth: true

            text: "One"
        }
        Button {
            Layout.fillWidth: true

            text: "Two"
        }

        Button {
            Layout.fillWidth: true

            text: "Three"
        }
        Button {
            Layout.fillWidth: true

            text: "Four"
        }

        // specific placement
        Button {
            Layout.row: 1
            Layout.column: 2
            Layout.fillWidth: true

            text: "Five"
        }

        // overflow into next row still works
        Label {
            text: "File"
        }

        // spanning two columns, same row
        TextField {
            Layout.columnSpan: 2
            Layout.fillWidth: true

            placeholderText: "Enter filename"
        }//<-- hide

        Label {
            text: "Comment"
        }

        TextArea {
            Layout.columnSpan: 2
            Layout.rowSpan: 4
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Button  {
            Layout.row: 6
            Layout.column: 0

            text: "Send"
        }
    }
    //<-- slide
}
