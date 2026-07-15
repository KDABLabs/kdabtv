// SPDX-License-Identifier: BSD-2-Clause
//
// Copyright (C) 2016, Haihua Hu <jared.hu@nxp.com>
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// a) Redistributions of source code must retain the above copyright notice,
//    this list of conditions and the following disclaimer.
//
// b) Redistributions in binary form must reproduce the above copyright
//    notice, this list of conditions and the following disclaimer in
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF
// THE POSSIBILITY OF SUCH DAMAGE.

import QtQuick 2.4
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.15
import QtQuick.Layouts 1.15
import QtMultimedia 5.15

import QtQuick.Window 2.1

ApplicationWindow {
    id: window
    visible: true
    title: " STREAMED APP ON DESKTOP "


    width: 1200
    height: 900
    x: 30
    y: 30
    color: colors.greyLight

    readonly property Colors colors: Colors {
    }

    component Colors: QtObject {
        readonly property color black: "#000000"
        readonly property color grey: "#5A5A5A"
        readonly property color greyDark: "#232323"
        readonly property color greyLight: "#6D6D6D"
        readonly property color red: "#CC1F25"
        readonly property color kdabBlue: "#0075c9"
        readonly property color white: "#FFFFFF"
    }

    header: ToolBar {
        height: 50
        background: Rectangle{
            anchors.fill: parent
            color: colors.greyDark
        }

        Image{
            Layout.alignment: Qt.AlignLeft
            height: parent.height * 1.5
            fillMode: Image.PreserveAspectFit
            smooth: true
            antialiasing: true
            mipmap: true

            Layout.margins: 10

            source: "qrc:///kdab_logo.png"

        }

        PageIndicator {
            id: indicator
            Layout.leftMargin: 20

            count: 2
            currentIndex: verticalView.currentIndex != 1 ? -1 : view.currentIndex

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.horizontalCenterOffset: 7
        }

        PageIndicator {
            id: indicatorvertical
            rotation: 90

            count: verticalView.count
            currentIndex: view.currentIndex != 0 ? -1 : verticalView.currentIndex

            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }


    SwipeView {
        id: verticalView

        anchors.fill: parent
        orientation: Qt.Vertical

        currentIndex: 1
        interactive: false

        WebRTCTopPage {
             id: pageTop
        }

        SwipeView {
            id: view
            currentIndex: 0
            interactive: false

            WebRTCCenterPage {
                id: pagecenter
            }

            WebRTCRightPage {
                id: pageright
                onDialogueRequested: dialog.open()
            }
        }

        WebRTCBottomPage {
            id: pagebottom
        }
    }


    PageChangeButton {
        id: buttonRight

        labelText: "→"
        anchors.right: parent.right
        anchors.rightMargin: 5

        anchors.verticalCenter: parent.verticalCenter


        visible: view.currentIndex !== 1  && verticalView.currentIndex === 1
        onClicked: view.currentIndex = view.currentIndex+1
    }

    PageChangeButton {
        id: buttonLeft

        labelText: "←"
        anchors.left: parent.left
        anchors.leftMargin: 7

        anchors.verticalCenter: parent.verticalCenter

        visible: view.currentIndex !== 0 && verticalView.currentIndex === 1
        onClicked: view.currentIndex = view.currentIndex-1
    }


    PageChangeButton {
        id: buttonUp

        labelText: "↑"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 5
        anchors.top: parent.top
        visible: verticalView.currentIndex !== 0

        onClicked: verticalView.currentIndex = verticalView.currentIndex-1

    }


    PageChangeButton {
        id: buttonDown

        labelText: "↓"
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 13
        anchors.horizontalCenter: parent.horizontalCenter

        visible: verticalView.currentIndex !== 2
        onClicked: verticalView.currentIndex = verticalView.currentIndex+1
    }



    WebRTCDialog {
        id: dialog
    }
}
