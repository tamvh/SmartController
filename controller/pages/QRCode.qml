/****************************************************************************
**
** Copyright (C) 2015 The Qt Company Ltd.
** Contact: http://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

import QtQuick 2.6
import QtQuick.Window 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtMultimedia 5.6
import Qt.labs.settings 1.0
import SmartControls 1.0
import QZXing 2.3
import "Common.js" as Global

Page {
    id: pageQRCode
    title: "Scan QR Code"
    Settings {
        id: settings
        property string style: "Universal"
    }

    header:ToolBar {
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            color: "black"
            opacity: 0.5
        }
        RowLayout {
            spacing: 20
            anchors.fill: parent


            ToolButton {
                Image {
                    id: backDraw
                    height: 16
                    width: 16
                    source: "qrc:/images/navigation_previous_item.png"
                    anchors.centerIn: parent
                }
                onClicked: stackView.pop();
            }

            Label {
                id: titleLabel
                text: title
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            ToolButton {
                contentItem: Image {
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/menu.png"
                }
                onClicked: optionsMenu.open()

                Menu {
                    id: optionsMenu
                    x: parent.width - width
                    transformOrigin: Menu.TopRight

                    MenuItem {
                        id: menuFlash
                        text: "Flash[OFF]"
                        onTriggered: {
                            console.log("menu flash")
                            camera.flash.mode = Camera.FlashOn
                            camera.exposure.exposureCompensation = -1.0
                            menuFlash.text = "Flash[ON]"
                        }
                    }
                    MenuItem {
                        text: "Focus"
                        onTriggered: {
                            console.log("menu focus")

                        }
                    }
                }
            }
        }
    }

    Rectangle
    {
        id: bgRect
        height: Screen.height
        width: Screen.width
        color: "white"
        Label
        {
            id: txtResult
            wrapMode: Text.Wrap
            font.pixelSize: 20
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter;
            z: 50
        }
        Rectangle {
            id: rectTOP
            anchors.top: parent.top
            width: Screen.width
            height: Screen.height/4
            color: "black"
            z:20
            opacity: 0.5


        }

        Rectangle {
            id: rectBOTTOM
            anchors.bottom: parent.bottom
            width: Screen.width
            height: Screen.height/4 + 50
            color: "black"
            z:20
            opacity: 0.5
        }

        Rectangle {
            id: rectLEFT
            anchors.left: parent.left
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Screen.height/4 + 50
            anchors.top: rectTOP.bottom
            width: (Screen.width - (Screen.height*2)/4 + 50) / 2
            height: parent.width;
            color: "black"
            z:20
            opacity: 0.5
        }

        Rectangle {
            id: rectRIGHT
            anchors.right: parent.right
            anchors.bottom: parent.bottom
            anchors.bottomMargin: Screen.height/4 + 50
            anchors.top: rectTOP.bottom
            width: (Screen.width - (Screen.height*2)/4 + 50) / 2
            height: parent.width;
            color: "black"
            z:20
            opacity: 0.5
        }

        Canvas {
            id: canvasTopLeft
            anchors {
                top: rectTOP.bottom
                left: rectLEFT.right
            }
            width: 50
            height: 50
            onPaint: {
                var ctx = getContext("2d");
                ctx.beginPath();
                ctx.lineWidth = 2
                ctx.strokeStyle = "red"
                ctx.rect(0, 0, 200, 200)
                ctx.stroke();
            }
            z:21
        }

        Canvas {
            id: canvasTopRight
            anchors {
                top: rectTOP.bottom
                right: rectRIGHT.left
            }
            width: 50
            height: 50
            onPaint: {
                var ctx = getContext("2d");
                ctx.beginPath();
                ctx.lineWidth = 2
                ctx.strokeStyle = "red"
                ctx.rect(0, 0, 200, 200)
                ctx.stroke();
            }
            rotation: 90
            z:21
        }

        Canvas {
            id: canvasBottomRight
            anchors {
                bottom: rectBOTTOM.top
                right: rectRIGHT.left
            }
            width: 50
            height: 50
            onPaint: {
                var ctx = getContext("2d");
                ctx.beginPath();
                ctx.lineWidth = 2
                ctx.strokeStyle = "red"
                ctx.rect(0, 0, 200, 200)
                ctx.stroke();
            }
            rotation: 180
            z:21
        }

        Canvas {
            id: canvasBottomLeft
            anchors {
                bottom: rectBOTTOM.top
                left: rectLEFT.right
            }
            width: 50
            height: 50
            onPaint: {
                var ctx = getContext("2d");
                ctx.beginPath();
                ctx.lineWidth = 2
                ctx.strokeStyle = "red"
                ctx.rect(0, 0, 200, 200)
                ctx.stroke();
            }
            rotation: -90
            z:21
        }

        Camera
        {
            id:camera            
            imageProcessing.whiteBalanceMode: CameraImageProcessing.WhiteBalanceFlash
            captureMode: Camera.CaptureStillImage
            exposure {
                exposureMode: Camera.ExposureAuto
            }

            focus {
                focusMode: Camera.FocusContinuous
                focusPointMode: Camera.FocusPointCenter
            }


        }

        VideoOutput
        {
            id: videoOutput
            source: camera
            anchors.top: parent.bottom
            anchors.bottom: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            rotation: -90
            filters: [ zxingFilter ]
            //display focus areas on camera viewfinder:
            Repeater {
                model: camera.focus.focusZones
                Rectangle {
                    id: rectFocus
                    anchors.centerIn: parent
                    height: Screen.width/1.5
                    width: Screen.width/1.5
                    Component.onCompleted: {
                        console.log("height: " + rectFocus.height);
                    }
                    opacity: 0.0
                }
            }
        }



        QZXingFilter
        {
            id: zxingFilter

            onDecodingStarted:
            {

            }

            onDecodingFinished:
            {
                if(succeeded)
                {

                }
                else
                {

                }
            }

            onTagFound:
            {
                console.log("--!!--");
                console.log(tag);
                stackView.push("qrc:/pages/AddDevice.qml", {_tag:tag});
            }
        }
    }
}
