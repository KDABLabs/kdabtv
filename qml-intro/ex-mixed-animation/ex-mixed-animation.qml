/*************************************************************************
 *
 * Copyright (c) 2013-2019, Klaralvdalens Datakonsult AB (KDAB)
 * All rights reserved.
 *
 * See the LICENSE.txt file shipped along with this file for the license.
 *
 *************************************************************************/


import QtQuick 2.0

Rectangle {
  color : "black"
  width : 200
  height : 200

  Image {
    id : rocket
    source : "../images/launch.svg"
    anchors.centerIn : parent

    ParallelAnimation {
      running : true
      SequentialAnimation {
        NumberAnimation { target : rocket; property:"opacity"; to : 0; duration : 1000 }
        PauseAnimation { duration: 500 }
      }
      SequentialAnimation {
        PauseAnimation { duration: 500 }
        NumberAnimation { target : rocket; property:"scale"; to : 0; duration : 1000 }
      }
    }
  }
}
