/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Grid {
    x: 15; y: 15; width: 300; height: 300

    columns: 2; rows: 2; spacing: 20

    Rectangle { width: 125; height: 125; color: "red" }
    Rectangle { width: 125; height: 125; color: "green" }
    Rectangle { width: 125; height: 125; color: "silver" }
    Rectangle { width: 125; height: 125; color: "blue" }
}
