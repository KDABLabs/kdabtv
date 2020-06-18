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

        spacing: 10

        RowLayout {
            spacing: 10

            Button {
                text: "One"
            }
            Button {
                text: "Two"
            }
            Button {
                text: "Three"
            }
        }

        RowLayout {
            spacing: 10
            layoutDirection: Qt.RightToLeft

            Button {
                text: "One"
            }
            Button {
                text: "Two"
            }
            Button {
                text: "Three"
            }
        }

        RowLayout {
            spacing: 10

            Button {
                text: "One"
            }
            Button {
                text: "Two"
            }
            Button {
                Layout.fillWidth: true

                text: "Three"
            }
        }

        RowLayout {
            spacing: 10

            Button {
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
        }

        RowLayout {
            Button {
                text: "One"
            }

            // Spacer item
            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "Two"
            }

            // Horizontal spacer item
            Item {
                Layout.fillWidth: true
            }

            Button {
                text: "Three"
            }
        }

        // Vertical spacer item
        Item {
            Layout.fillHeight: true
        }
    }
}
