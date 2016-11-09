import QtQuick 2.0
import Material 0.2
import SmartControls 1.0

Page {
    property alias deviceId: deviceDetailController.deviceId
    title: "Thông tin thiết bị"

    actions: [
        Action {
            iconName: "action/schedule"
            onTriggered: push(deviceCalendar_component, { deviceId:deviceDetailController.deviceId })
        }
    ]

    DeviceDetailController {
        id: deviceDetailController
    }

    Item {
        id: deviceInfo
        width: parent.width
        height: Units.dp(100)

        Item {
            width: parent.width
            height: Units.dp(100)

            Icon {
                id: icon
                width: Units.dp(70)
                height: Units.dp(70)
                anchors {
                    left: parent.left
                    leftMargin: Units.dp(10)
                    verticalCenter: parent.verticalCenter
                }
                name: "device/bluetooth"
                color: "#0A3D91"
                size: Units.dp(48)
            }
            Column {
                anchors {
                    left: icon.right
                    leftMargin: Units.dp(10)
                    right: parent.right
                    rightMargin: Units.dp(10)
                    verticalCenter: parent.verticalCenter
                }
                spacing: Units.dp(5)
                Text {
                    text: deviceDetailController.deviceName
                    font { pixelSize: Units.dp(16); }
                    color: deviceDetailController.deviceState?"#1eb19b":"#6c6c6c"
                    font.bold: deviceDetailController.deviceState?true:false
                    height: Units.dp(25)
                    width: parent.width
                }
                Row {
                    width: 2*Units.dp(100)
                    height: Units.dp(38)
                    spacing: Units.dp(20)

                    Text {
                        width: Units.dp(60)
                        height: Units.dp(38)
                        verticalAlignment: Text.AlignVCenter
                        text: deviceDetailController.deviceState?"Đang bật":"Đang tắt"
                        font { pixelSize: Units.dp(14); }
                        visible: true
                    }

                    Button {
                        width: Units.dp(100)
                        height: Units.dp(38)
                        elevation: 1
                        text: deviceDetailController.deviceState?"Tắt":"Bật"
                        textColor: "white"

                        onClicked: {
                            console.log("onClicked Turn on")
                            showLoadingView()
                            deviceDetailController.turnPlug(deviceDetailController.deviceAddress, deviceDetailController.deviceState?false:true)
                        }
                    }
                }
            }
        }

        Rectangle {
            height: Units.dp(0.5)
            width: parent.width
            color: "gray"
            anchors.bottom: parent.bottom
        }
    }

    Button {
        height: Units.dp(48)
        elevation: 1
        backgroundColor: "#ffa726"

        anchors {
            top: deviceInfo.bottom
            topMargin: Units.dp(20)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }

        text: "Đồng bộ thời gian"

        onClicked: {
            upDeviceTime(_deviceId, _deviceAddress)
            showLoadingView()
        }
    }
}
