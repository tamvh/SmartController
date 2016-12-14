import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import SmartControls 1.0
import "Common.js" as Global
import "utils.js" as Utils

Page {
    id: pageDeviceDetailType4
    title: "Device Detail"
    property var _deviceId: ""
    property var _deviceName: ""
    property var _deviceaddress: ""
    property var _groupname: ""
    property var _power: 0
    property var _valueBrightnessInc: 1
    property var _valueBrightnessDesc: 2

    property real h
    property real s : 1
    property real v : 1
    property color color1 /*: Utils.hsvToHsl(0.6,1.0,1.0)*/
    signal changeColor(color color1);
    signal mouseRelease();
    //visible: true
    property real ringWidth: 0.60

    Settings {
        id: settings
        property string style: "Universal"
    }

    DeviceController {
        id: deviceController
    }

    header:ToolBar {
        background: Rectangle {
            id: header
            implicitWidth: 100
            implicitHeight: 25
            color: "lightblue"
        }
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                Image {
                    id:imgBack
                    height: 16
                    width: 16
                    source: "qrc:/images/navigation_previous_item.png"
                    anchors {
                        centerIn: parent
                    }
                }
                ColorOverlay {
                    anchors.fill: imgBack
                    source: imgBack
                    color: "#795548"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop();
                    }
                }
            }


            Label {
                id: titleLabel
                text: _deviceName
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "#795548"
            }

            ToolButton {
                Image {
                    id: imgClock
                    height: 16
                    width: 16
                    source: "qrc:/images/clock.png"
                    anchors {
                        centerIn: parent
                    }
                }
                ColorOverlay {
                    anchors.fill: imgClock
                    source: imgClock
                    color: "#795548"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("_deviceId: " + _deviceId);
                        stackView.push("qrc:/pages/Alarm.qml", {_deviceId: _deviceId, _deviceName: _deviceName, _groupname: _groupname});
                    }
                }
            }
        }
    }
    Rectangle {
        width: parent.width
        height: parent.height
        color: "lightblue"
        // View Cool - Warm
        Grid {
            id: listRGB
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 20
            }
            columns: 2
            spacing: 20

            Rectangle {
                id: rectCool
                height: 40
                width: 80
                border.color: "#03A9F4"
                border.width: 0.5
                radius: 5
                Label {
                    id: lblValueCool
                    anchors.centerIn: parent
                    color: "#03A9F4"
                    text: "0"
                }
            }
            Rectangle {
                id: rectWarm
                height: 40
                width: 80
                border.color: "#FFD600"
                border.width: 0.5
                radius: 5
                Label {
                    id: lblValueWarm
                    anchors.centerIn: parent
                    color: "#FFD600"
                    text: "0"
                }
            }
        }

        Item {
            id: squareSV
            width: 300
            height: 300
            anchors.centerIn: parent

            Rectangle {
                anchors.fill: parent;
                rotation: -90
                gradient: Gradient {
                    GradientStop {position: 0.0; color: "#03A9F4"}
                    GradientStop {position: 1.0; color: "#FFD600"}
                }
            }

            Rectangle {
                anchors.fill: parent
                gradient: Gradient {
                    GradientStop {position: 1.0; color: "#00000000"}
                    GradientStop {position: 0.0; color: "#F1F8E9"}
                }
            }

            // Saturation/Value picker - dau cham ben trong
            Item {
                id: pickerSV
                x: s * parent.width
                y: (1 - v) * parent.height
                property int radiusPickerSV: 5

                Rectangle {
                    x: -parent.radiusPickerSV
                    y: -parent.radiusPickerSV
                    width: parent.radiusPickerSV * 5
                    height: parent.radiusPickerSV * 5
                    radius: parent.radiusPickerSV*5
                    border.color: (pickerSV.x > squareSV.width / 2) || (pickerSV.y > squareSV.height / 2) ? "white" : "black"
                    border.width: 2
                    color: "transparent"
                    antialiasing: true
                }
            }

            MouseArea {
                anchors.fill: parent
                function handleMouseSV(mouse) {
                    if (mouse.buttons & Qt.LeftButton) {
                        s = Math.max(0, Math.min(width, mouse.x)) / parent.width
                        v = 1 - Math.max(0, Math.min(height, mouse.y)) / parent.height
                        color1 = Utils.hsvToHsl(h, s, v, 1)
                        lblValueWarm.text = (color1.r*255).toFixed(0)
                        lblValueCool.text = (color1.g*255).toFixed(0)
                        changeColor(color1)

                    }
                }
                onPositionChanged: handleMouseSV(mouse)
                onPressed: handleMouseSV(mouse)
                onReleased: mouseRelease()
            }
        }
    }

    Label {
        id: lblVoltage
        text: "Voltage: 0W"
        color: "red"
        anchors {
            bottom: parent.bottom
            horizontalCenter: parent.horizontalCenter
        }
    }
}
