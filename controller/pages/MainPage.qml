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
import QtQuick.Window 2.2
import SmartControls 1.0

ApplicationWindow {
    id: window
    width: 360
    height: 520
    visible: true
    title: "Dashboard"    

    property string imgTitle: "Dashboard"
    Settings {
        id: settings
        property string style: "Universal"
    }

    Drawer {
        id: drawer
        z: 1
        width: window.width/1.2;
        height: window.height;
        Rectangle {
            id: rectHeader
            height: 150
            width: parent.width
            color: "#EF6C00"
            Image {
                id: imgUser
                source: "qrc:/images/user.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter

            }
            Label {
                id: lblUserName
                text: "no name"
                color: "white"
                anchors {
                    top: imgUser.bottom
                    topMargin: 10
                }
                anchors.horizontalCenter: parent.horizontalCenter
            }
        }
        Rectangle {
            height: parent.height - rectHeader.height
            width: parent.width
            anchors {
                top: rectHeader.bottom
            }
            ListView {
                id: listView
                currentIndex: -1
                anchors.fill: parent
                clip: true
                displaced: Transition {
                    NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
                }
                delegate: ItemDelegate {
                    width: parent.width
                    height: 50
                    RowLayout {
                        id: subMenu
                        anchors {
                            fill: parent
                        }

                        ToolButton {
                            Image {
                                anchors.centerIn: parent
                                source: iconSource
                                height: 20
                                width: 20
                            }

                            onClicked: {
                                stackView.push(model.source)
                                drawer.close()
                            }
                        }

                        Label {
                            text: title
                            font.pixelSize: 13
                            elide: Label.ElideRight
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                    }
                    Rectangle {
                        anchors {
                            left: parent.left
                            right: parent.right
                        }

                        color: "#E0E0E0"
                        height: 0.5
                    }

                    highlighted: ListView.isCurrentItem
                    onClicked: {
//                        if (listView.currentIndex != index) {
                        listView.currentIndex = index
                        imgTitle = model.title
                        stackView.clear()
                        if(model.source !== "qrc:/pages/Dashboard.qml") {
                            stackView.push("qrc:/pages/Dashboard.qml")
                        }
                        stackView.push(model.source)
//                        }
                        drawer.close()
                    }
                }

                model: ListModel {
                    ListElement {iconSource : "qrc:/images/menu_dashboard.png"; title: "Home"; source: "qrc:/pages/Dashboard.qml" }
                    ListElement {iconSource : "qrc:/images/menu_search.png"; title: "Scan Device"; source: "qrc:/pages/ScanDevice.qml" }
                    ListElement {iconSource : "qrc:/images/menu_qrcode.png"; title: "Scan QR Code"; source: "qrc:/pages/QRCode.qml" }
                    ListElement {iconSource : "qrc:/images/menu_key.png"; title: "Security Key"; source: "qrc:/pages/SecurityKey.qml" }
                    ListElement {iconSource : "qrc:/images/menu_settings.png"; title: "Settings"; source: "qrc:/pages/Setting.qml" }
                    ListElement {iconSource : "qrc:/images/menu_sync.png"; title: "Sync"; source: "qrc:/pages/Sync.qml" }
                    ListElement {iconSource : "qrc:/images/menu_sync.png"; title: "Test Color"; source: "qrc:/pages/EColorPicker.qml" }
                }
                ScrollIndicator.vertical: ScrollIndicator { }
            }
        }

    }

    StackView {
        id: stackView
        anchors.fill: parent
        focus: true
        Keys.onReleased: if (event.key === Qt.Key_Back && stackView.depth > 1) {
                             stackView.pop();
                             event.accepted = true;
                         }

        initialItem: mainpage
        Dashboard
        {
            id: mainpage            
        }
    }    
}
