/*************************************************************************
 *
 * Copyright (c) 2017-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0
import QtQuick.Controls 1.1

ApplicationWindow {
    width: 800
    height: 600

    TabView {
        anchors.fill: parent

        Tab {
            title: "Resizing and Stretching"
            ResizingPage {}
        }

        Tab {
            title: "Alignment"
            AlignmentPage {}
        }

        Tab {
            title: "Resize & Align"
            ResizeAndAlignPage {}
        }

        Tab {
            title: "Grid"
            GridPage {}
        }
    }
}
