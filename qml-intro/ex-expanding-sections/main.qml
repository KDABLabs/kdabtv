/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

ListView {
    id: view

    property var collapsed: ({})

    width: 150
    height: 250
    focus: true
    clip: true

    model: NameModel { }

    delegate: NameDelegate {
        readonly property ListView __lv: ListView.view

        anchors {
            left: parent.left
            leftMargin: 2

            right: parent.right
            rightMargin: 2
        }

        expanded: view.isSectionExpanded( model.team )

        MouseArea {
            anchors.fill: parent
            onClicked: __lv.currentIndex = index
        }
    }

    highlight: HighlightDelegate {
        width: parent.width
        anchors {
            left: parent.left
            right: parent.right
        }
    }

    section {
        property: "team"
        criteria: ViewSection.FullString

        delegate: SectionDelegate {
            anchors {
                left: parent.left
                right: parent.right
            }

            text: section

            onClicked: view.toggleSection( section )
        }
    }

    function isSectionExpanded( section ) {
        return !(section in collapsed);
    }

    function showSection( section ) {
        delete collapsed[section]
        /*emit*/ collapsedChanged();
    }

    function hideSection( section ) {
        collapsed[section] = true
        /*emit*/ collapsedChanged();
    }

    function toggleSection( section ) {
        if ( isSectionExpanded( section ) ) {
            hideSection( section )
        } else {
            showSection( section )
        }
    }
}
