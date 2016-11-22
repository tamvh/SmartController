import QtQuick 2.1
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
    id: pageDeviceDetailType5
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
        height: parent.height
        width: parent.width
        color: "white"

        //line
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
                leftMargin: 0
                rightMargin: 0
            }
            color: "#795548"
            height: 0.5
        }

        // View RBG
        Grid {
            id: listRGB
            anchors {
                horizontalCenter: parent.horizontalCenter
                top: parent.top
                topMargin: 20
            }
            columns: 3
            spacing: 20
            Rectangle {
                id: rectR
                height: 40
                width: 80
                border.color: "red"
                border.width: 0.5
                radius: 5
                Label {
                    id: lblValueR
                    anchors.centerIn: parent
                    color: "red"
                    text: "0"
                }
            }
            Rectangle {
                id: rectG
                height: 40
                width: 80
                border.color: "green"
                border.width: 0.5
                radius: 5
                Label {
                    id: lblValueG
                    anchors.centerIn: parent
                    color: "green"
                    text: "0"
                }
            }
            Rectangle {
                id: rectB
                height: 40
                width: 80
                border.color: "blue"
                border.width: 0.5
                radius: 5
                Label {
                    id: lblValueB
                    anchors.centerIn: parent
                    color: "blue"
                    text: "0"
                }
            }
        }

        //View color area
        Rectangle {
            id: rectContent
            width: 300
            height: 300
            smooth: true



            onColorChanged: setColor()
            color : "transparent"

            function setColor(r,g,b) {
                    var hsvColor = Utils.rgbToHsv(r,g,b)
                    h = hsvColor.h
                    color1.r = r/255;color1.g = g/255; color1.b = b/255;
                    //s = hsvColor.s
                   // v = hsvColor.v
            }
            anchors {
                top: listRGB.bottom
                centerIn: parent
            }

            // Color ring
            Item {
                id: outerCircle
                anchors.fill: parent
                smooth : true
                //antialiasing: true
                Image {
                    id: bground
                    anchors.fill: parent
                    source: "qrc:/images/colorpickerImage.png"
                    sourceSize: Qt.size(parent.width, parent.height)
                    smooth: true
                    visible: true
                }

                // Hue picker - kim quet vong tron
                Rectangle {
                    id: pickerHue
                    property int sizePickerHue: 3

                    x: parent.width / 2
                    y: (parent.height - sizePickerHue) / 2
                    //width: parent.width/2
                    width: parent.width/2
                    height: sizePickerHue
                    color: "white"
                    antialiasing: true
                    transform: Rotation {
                        id: pickerHueAngle
                        origin.x: 0
                        origin.y: pickerHue.height / 2
                        angle: (1 - h) * 360
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    function handleMouseHue(mouse) {
                        if (mouse.buttons & Qt.LeftButton) {
                            var radianAngle = Math.atan2(outerCircle.height / 2 - mouse.y, mouse.x - outerCircle.width / 2)
                            var degreeAngle = (1 - radianAngle * 0.5 / Math.PI)
                            h = degreeAngle < 1 ? 1 - degreeAngle : 2 - degreeAngle
                            color1 = Utils.hsvToHsl(h, s, v, 1)
                            lblValueR.text = (color1.r*255).toFixed(0)
                            lblValueB.text = (color1.b*255).toFixed(0)
                            lblValueG.text = (color1.g*255).toFixed(0)
                            changeColor(color1)
                        }
                    }
                    onPositionChanged: handleMouseHue(mouse)
                    onPressed: handleMouseHue(mouse)
                    onReleased: mouseRelease()
                }


                // Clearing inner circle
                Rectangle {
                    id: innerCircle
                    width: outerCircle.width * ringWidth
                    height: outerCircle.height * ringWidth
                    anchors.centerIn: parent
                    radius: outerCircle.width * ringWidth / 2
                    antialiasing: true
                    color : "grey"
                }

                // Color square - khung vuong ben trong
                Item {
                    id: squareSV
                    width: outerCircle.width * ringWidth / Math.sqrt(2)
                    height: outerCircle.width * ringWidth / Math.sqrt(2)
                    anchors.centerIn: parent

                    Rectangle {
                        anchors.fill: parent;
                        rotation: -90
                        gradient: Gradient {
                            GradientStop {position: 0.0; color: "white"}
                            GradientStop {position: 1.0; color: Qt.hsla(h, 1, 0.5, 1)}
                        }
                    }
                    Rectangle {
                        anchors.fill: parent
                        gradient: Gradient {
                            GradientStop {position: 1.0; color: "#FF000000"}
                            GradientStop {position: 0.0; color: "#00000000"}
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
                                lblValueR.text = (color1.r*255).toFixed(0)
                                lblValueB.text = (color1.b*255).toFixed(0)
                                lblValueG.text = (color1.g*255).toFixed(0)
                                changeColor(color1)

                            }
                        }
                        onPositionChanged: handleMouseSV(mouse)
                        onPressed: handleMouseSV(mouse)
                        onReleased: mouseRelease()
                    }
                }
            }
        }
    }
}
