/*************************************************************************
 *
 * Copyright (c) 2010-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/

import QtQuick 2.0

Rectangle {
  id: bg
  width: 400; height: 200
  color: "lightblue"

  Image { id: book; source: "../images/book.svg"
          anchors.left: bg.left
          anchors.leftMargin: bg.width/16
          anchors.verticalCenter: bg.verticalCenter }

  Text { text: "Writing"; font.pixelSize: 32
         anchors.left: book.right
         anchors.leftMargin: 32
         anchors.baseline: book.verticalCenter }
}
