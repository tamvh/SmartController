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
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import SmartControls 1.0
import "Common.js" as Global

Page {
    title: "Scan Device"
    Settings {
        id: settings
        property string style: "Universal"
    }


    header:ToolBar {
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            color: "#EF6C00"
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
                onClicked: {
                    stackView.pop();
                }
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
                        text: "Settings"
                        onTriggered: {
                            stackView.push("qrc:/pages/Setting.qml")
                        }
                    }
                    MenuItem {
                        text: "Exit"
                        onTriggered: Qt.quit();
                    }
                }
            }
        }
    }


    DeviceScanningController {
        id: controller
    }

    ListView {
        id: deviceListView
        anchors {
            top: parent.top
            bottom: btnScanDevice.top
            left: parent.left
            right: parent.right
        }
        clip: true
        model: controller.deviceList
        delegate: scanningItemDelegate
    }


    Button {
        id: btnScanDevice
        height: 45
        anchors {
            left: parent.left
            leftMargin: 10
            right: parent.right
            rightMargin: 10
            bottom: parent.bottom
            bottomMargin: 10

        }

        background: Rectangle {
            id: bgRectButton
            implicitWidth: 100
            implicitHeight: 25
            border.width: 1
            border.color: "#EEEEEE"
            radius: 30
            color: "white"
        }


        onClicked: {
            console.log("btnScanDevice onClicked Turn on")
            bgRectButton.color = "white"
            if (controller.scanningState == 0) {
                controller.startScanDevices()
            } else {
                controller.stopScanDevices()
            }
        }

        onPressed: {
            console.log("btnScanDevice onPressed Turn on")
            bgRectButton.color = "#EEEEEE"
        }

        BusyIndicator {
            id:progress
            visible: controller.scanningState == 1
            width: 30
            height: 30
            anchors {
                right: buttonTitle.left
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }

            running: image.status === Image.Loading
        }

        Image {
            id: icon
            visible: controller.scanningState == 0
            width: 20
            height: 20
            anchors {
                right: buttonTitle.left
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/images/menu_search.png"
        }

        Text {
            id: buttonTitle
            text: controller.scanningState == 0?"Tìm kiếm":"Tạm dừng"
            font.family: "Helvetica"
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: "#424242"
        }
    }


    Component {
        id: scanningItemDelegate
        Item {
            width: parent.width
            height: 90
            Image {
                id: icon
                width: 60
                height: 60
                anchors {
                    right: buttonTitle.left
                    rightMargin: 10
                    verticalCenter: parent.verticalCenter
                }
                source: "qrc:/images/bluetooth.png"
            }
            Item {
                id: rightItem
                visible: hasLampService ? true : false
                anchors {
                    top: parent.top
                    topMargin: 10
                    right: parent.right
                    rightMargin: 10
                    bottom: parent.bottom
                    bottomMargin: 10
                }
                width: 50
            }

            Column {
                id: deviceInfo
                anchors {
                    left: icon.right
                    leftMargin: 10
                    right: rightItem.right
                    rightMargin: 10
                    top: parent.top
                    topMargin: 10
                }
                spacing: 5
                Text {
                    text: deviceName
                    font {
                        pixelSize: 16
                        family: "Helvetica"
                    }
                    color: "#485C68"
                    height: 25
                    width: parent.width
                }
                Text {
                    height: 25
                    width: parent.width
                    text: deviceAddress
                    font {
                        pixelSize: 14
                        family: "Helvetica"
                    }
                    color: "#485C68"
                    wrapMode: Text.WordWrap
                    clip: true
                }
            }

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    stackView.push("qrc:/pages/AddDevice.qml", {_deviceAddress: deviceAddress, _deviceName: deviceName, _page: "ScanDevice"});

                }
            }

            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                }

                color: Qt.rgba(0,0,0,0.1)
                height: 1
            }
        }
    }
}
