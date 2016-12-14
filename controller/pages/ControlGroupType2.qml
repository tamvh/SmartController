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

Page {
    id: pageControlGroupDeviceType2
    title: "Device Detail"
    property var _deviceId: ""
    property var _deviceName: ""
    property var _deviceaddress: ""
    property var _groupName: ""
    property var _groupId: 0
    property var _power: 0
    property var _valueBrightnessInc: 1
    property var _valueBrightnessDesc: 2
    property var _value: 0
    property var _command: 2
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
                text: _groupName
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
        id: rectIcon
        height: parent.height/2;
        width: parent.width;
        Rectangle {
            id: rectHeader
            height: parent.height;
            width: parent.width;
            color: "lightblue";
            Image {
                id: icoLamp
                source: "qrc:/images/light_type_2_off.png"
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.verticalCenter: parent.verticalCenter
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectIcon onClicked");
                    }
                }
            }

            Text {
                id: txtVoltage
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: parent.bottom
                anchors.bottomMargin: 5
                text: qsTr("Voltage")
                font.pixelSize: 10
            }
            Text {
                id: txtVoltageValue
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.bottom: txtVoltage.top
                text: qsTr("0W")
                font.pixelSize: 20
                color: "red"
                opacity: 0.8
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    console.log("PRESSED")
                    rectHeader.state = "PRESSED"
                    header.state = "PRESSED"
                    rectController.state = "PRESSED"
                }
                onReleased: {
                    console.log("RELEASED")
                    rectController.state = "RELEASED"
                    rectHeader.state = "RELEASED"
                    header.state = "RELEASED"
                }
            }
            states: [
                State {
                    name: "PRESSED"
                    PropertyChanges { target: header; color: "lightsteelblue"}
                    PropertyChanges { target: rectHeader; color: "lightsteelblue"}
                    PropertyChanges { target: rectController; color: "#F5F5F5"}
                },
                State {
                    name: "RELEASED"
                    PropertyChanges { target: header; color: "lightblue"}
                    PropertyChanges { target: rectHeader; color: "lightblue"}
                    PropertyChanges { target: rectController; color: "white"}
                }
            ]
            transitions: [
                Transition {
                    from: "PRESSED"
                    to: "RELEASED"
                    ColorAnimation { target: header; duration: 500}
                    ColorAnimation { target: rectHeader; duration: 500}
                    ColorAnimation { target: rectController; duration: 500}
                },
                Transition {
                    from: "RELEASED"
                    to: "PRESSED"
                    ColorAnimation { target: header; duration: 500}
                    ColorAnimation { target: rectHeader; duration: 500}
                    ColorAnimation { target: rectController; duration: 500}
                }
            ]
        }
    }

    Rectangle {
        id: rectController
        width: parent.width
        height: parent.height/2
        anchors.top: rectIcon.bottom
        Image {
            id: icPower
            source: "qrc:/images/ic_power.png"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    if(_value === 0) {
                        _value = 1;
                        icoLamp.source = "qrc:/images/light_type_2_on.png"
                    }
                    else {
                        _value = 0;
                        icoLamp.source = "qrc:/images/light_type_2_off.png"
                    }
                    deviceController.controlDeviceSimpleLight(
                                _deviceId,
                                _deviceaddress,
                                _command,
                                _value);
                }
                onPressed: {
                    rectController.color = "#CFD8DC";
                }
                onReleased: {
                    rectController.color = "white";
                }
            }
        }
    }
}
