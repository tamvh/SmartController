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
    id: pageDeviceDetailType1
    title: "Device Detail"
    property var _deviceId: ""
    property var _deviceName: ""
    property var _deviceaddress: ""
    property var _groupname: ""
    property var _power: 0
    property var _valueBrightnessInc: 1
    property var _valueBrightnessDesc: 2
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
                source: "qrc:/images/light_type_1.png"
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
                    rectHeader.state = "PRESSED"
                    header.state = "PRESSED"
                    rectController.state = "PRESSED"
                    console.log("PRESSED")
                }
                onReleased: {
                    rectController.state = "RELEASED"
                    rectHeader.state = "RELEASED"
                    header.state = "RELEASED"
                    console.log("RELEASED")
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
        Grid {
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            columns: 3
            spacing: 10
            Rectangle {
                id: rectBrightnessInc
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgBrightnessInc
                    height: 20
                    width: 20
                    source: "qrc:/images/brightnessinc.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgBrightnessInc.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Brightness +")
                    font.pixelSize: 11
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBrightnessInc onClicked")
                        rectBrightnessInc.color = "white"
                        rectBrightnessInc.border.color = "#E0E0E0";
                        deviceController.controlDevice(_deviceaddress, _valueBrightnessInc);
                    }

                    onPressed: {
                        console.log("rectBrightnessInc onPressed")
                        rectBrightnessInc.color = "#E0E0E0"
                        rectBrightnessInc.border.color = "#FB8C00";
                    }
                }
            }
            Rectangle {
                id: rectBrightnessWarm
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgBrightnessWarm
                    height: 20
                    width: 20
                    source: "qrc:/images/brightnesswarm.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgBrightnessWarm.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Warm +")
                    font.pixelSize: 11
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBrightnessInc onClicked")
                        rectBrightnessWarm.color = "white"
                        rectBrightnessWarm.border.color = "#E0E0E0";
                    }

                    onPressed: {
                        console.log("rectBrightnessInc onPressed")
                        rectBrightnessWarm.color = "#E0E0E0"
                        rectBrightnessWarm.border.color = "#FB8C00";
                    }
                }
            }
            Rectangle {
                id: rectNightLight
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgNightLight
                    height: 20
                    width: 20
                    source: "qrc:/images/nightlight.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgNightLight.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Night Light")
                    font.pixelSize: 11
                    color: "gray"
                }
                ColorOverlay {
                    anchors.fill: imgNightLight
                    source: imgNightLight
                    color: "black"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBrightnessInc onClicked")
                        rectNightLight.color = "white"
                        rectNightLight.border.color = "#E0E0E0";
                    }

                    onPressed: {
                        console.log("rectBrightnessInc onPressed")
                        rectNightLight.color = "#E0E0E0"
                        rectNightLight.border.color = "#FB8C00";
                    }
                }
            }
            Rectangle {
                id: rectBrightnessDesc
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgBrightnessDesc
                    height: 20
                    width: 20
                    source: "qrc:/images/brightnessdesc.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgBrightnessDesc.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Brightness -")
                    font.pixelSize: 11
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBrightnessInc onClicked")
                        rectBrightnessDesc.color = "white"
                        rectBrightnessDesc.border.color = "#E0E0E0";
                        deviceController.controlDevice(_deviceaddress, _valueBrightnessDesc);
                    }

                    onPressed: {
                        console.log("rectBrightnessInc onPressed")
                        rectBrightnessDesc.color = "#E0E0E0"
                        rectBrightnessDesc.border.color = "#FB8C00";
                    }
                }
            }
            Rectangle {
                id: rectBrightnessCool
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgBrightnessCool
                    height: 20
                    width: 20
                    source: "qrc:/images/brightnesscool.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgBrightnessCool.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Cool +")
                    font.pixelSize: 11
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBrightnessInc onClicked")
                        rectBrightnessCool.color = "white"
                        rectBrightnessCool.border.color = "#E0E0E0";
                    }

                    onPressed: {
                        console.log("rectBrightnessInc onPressed")
                        rectBrightnessCool.color = "#E0E0E0"
                        rectBrightnessCool.border.color = "#FB8C00";
                    }
                }
            }
            Rectangle {
                id: rectBalance
                width: rectController.width/4;
                height: rectController.width/4;
                border.width: 1
                border.color: "#E0E0E0"
                radius: rectController.width/4
                Image {
                    id: imgBalance
                    height: 20
                    width: 20
                    source: "qrc:/images/ic_balance.png"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Text {
                    anchors {
                        top: imgBalance.bottom
                        horizontalCenter: parent.horizontalCenter
                    }
                    text: qsTr("Balance")
                    font.pixelSize: 11
                    color: "gray"
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("rectBalance onClicked")
                        rectBalance.color = "white"
                        rectBalance.border.color = "#E0E0E0";
                    }

                    onPressed: {
                        console.log("rectBalance onPressed")
                        rectBalance.color = "#E0E0E0"
                        rectBalance.border.color = "#FB8C00";
                    }
                }
            }
        }
    }



    Component {
        id: pageListDevice_component
        ListDevice{

        }
    }
}
