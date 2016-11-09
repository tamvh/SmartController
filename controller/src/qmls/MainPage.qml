import QtQuick 2.5
import Material 0.2
import SmartControls 1.0
import QtQuick.Layouts 1.1
import QtQuick.Window 2.2


Page {
    id: page
    title: "Đèn ốp trần cao cấp"
    backgroundColor: "#ffffff"




    actions: [
        Action {
            name: "Print"

            // Icon name from the Google Material Design icon pack
            iconName: "content/add_circle_outline"
            onTriggered: page.push(scanningDevices_component)
        }
    ]


    DeviceListController {
        id: controller

        onChangeBrightSuccess: {
            console.log("onChangeBrightSuccess.........................")
            hideLoadingView()
            snackbar.open("Thay đổi độ sáng của bóng đèn thành công.");
        }

        onChangeBrightFail: {
            console.log("onChangeBrightFail.........................--")
            hideLoadingView()
            console.info(snackbar)
            snackbar.open("Có lỗi xảy ra trong quá trình thay đổi độ sáng của bóng đèn.")
        }

        onShowMsg: {
            hideLoadingView();
            console.log("onShowMsg.........................message:" + message)
        }

        onStartReadDevicesState: {
            console.log("onShowMsg.........................onReadDevicesStat start")
            showLoadingView();
        }

        onReadDeviceStateFinish: {
            console.log("onShowMsg.........................onReadDeviceState Finish")
            hideLoadingView();
        }

        onReadDeviceStateSuccess: {

        }

        onReadDeviceStateFail: {

        }
    }
        Item {
            width: Screen.width
//            height: Screen.height
            anchors {
                top: parent.top
                topMargin: Units.dp(20)
                left: icon.right
                leftMargin: Units.dp(10)
                right: rightItem.left
                rightMargin: Units.dp(10)
                verticalCenter: parent.verticalCenter
            }

            Column {
                spacing: Units.dp(10)
                Row {
    //                spacing: Units.dp(20)
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        id: brightPlus
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                        GradientStop { position: 0.0; color: "lightsteelblue" }
    //                        GradientStop { position: 1.0; color: "gray" }
    //                    }
                        color: 'lightsteelblue'
                        radius: Units.dp(20)
                        SequentialAnimation {
                            id: anim
                            PropertyAnimation {
                                target: light
                                property: "color"
                                to: "gray"
                                duration: 1000

                            }
                            PropertyAnimation {
                                target: light
                                property: "color"
                                to: "lightsteelblue"
                                duration: 1000

                            }
                        }
                        Text {
                            anchors.centerIn: parent
                            text: "Bright (+)"
                        }

                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 1)
    //                            controller.changeBright("E5:18:8B:47:A0:50E5:18:8B:47:A0:50E5:18:8B:47:A0:50", 1)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                }

                Row {
    //                spacing: Units.dp(20)
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                        GradientStop { position: 0.0; color: "lightsteelblue" }
    //                        GradientStop { position: 1.0; color: "gray" }
    //                    }
                        color: "lightsteelblue"
                        radius: Units.dp(20)
                        Text {
                            anchors.centerIn: parent
                            text: "Warm (+)"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 6)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }

                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }

                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                        GradientStop { position: 0.0; color: "lightsteelblue" }
    //                        GradientStop { position: 1.0; color: "blue" }
    //                    }
                        color: "#AF7AC5"
                        radius: Units.dp(70)
                        Text {
                            anchors.centerIn: parent
                            text: "|||"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                 controller.changeBright("E5:18:8B:47:A0:50", 3)
                            }
                            onPressAndHold: {
                                controller.changeBright("E5:18:8B:47:A0:50", 3)
                            }
                            onPressed: {
                                parent.color = '#A569BD'
                            }
                            onReleased: {
                                parent.color = '#AF7AC5'
                            }
                        }
                    }

                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }

                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                        GradientStop { position: 0.0; color: "lightsteelblue" }
    //                        GradientStop { position: 1.0; color: "gray" }
    //                    }
                        color: "lightsteelblue"
                        radius: Units.dp(20)
                        Text {
                            anchors.centerIn: parent
                            text: "Cool (+)"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 0)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }
                    Rectangle {
                        width: Screen.width/10;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                }

                Row {
    //                spacing: Units.dp(20)
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                        GradientStop { position: 0.0; color: "lightsteelblue" }
    //                        GradientStop { position: 1.0; color: "gray" }
    //                    }
                        color: "lightsteelblue"
                        radius: Units.dp(20)
                        Text {
                            anchors.centerIn: parent
                            text: "Night light"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 4)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                            GradientStop { position: 0.0; color: "lightsteelblue" }
    //                            GradientStop { position: 1.0; color: "gray" }
    //                        }
                        color: "lightsteelblue"
                        radius: Units.dp(20)
                        Text {
                            anchors.centerIn: parent
                            text: "Bright (-)"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 2)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
    //                    gradient: Gradient {
    //                            GradientStop { position: 0.0; color: "lightsteelblue" }
    //                            GradientStop { position: 1.0; color: "gray" }
    //                        }
                        color: "lightsteelblue"
                        radius: Units.dp(20)
                        Text {
                            anchors.centerIn: parent
                            text: "ON/OFF"
                        }
                        MouseArea {
                            anchors.fill: parent
                            onClicked: {
                                controller.changeBright("E5:18:8B:47:A0:50", 5)
                            }
                            onPressed: {
                                parent.color = '#5DADE2'
                            }
                            onReleased: {
                                parent.color = 'lightsteelblue'
                            }
                        }
                    }
                    Rectangle {
                        width: Screen.width/20;
                        height: Screen.width/(3*1.25);
                        color: "#ffffff"
                    }

                }
                Row {
                    Rectangle {
                        width: Screen.width/(3*1.25);
                        height: Screen.width/(3*1.25);
                        Image {
                               anchors.fill: parent
                               source: "logodotrang.jpg"
                               sourceSize.width: 1024
                               sourceSize.height: 1024
                            }
                    }
                }
            }

    }
    Component {
       id: deviceDetail_component
       DeviceDetailView {
       }
    }
    Component {
       id: deviceCalendar_component
       DeviceCalendarListView {}
    }
    Component {
       id: updateDeviceInfo_component
       UpdateDeviceInfo {
           onSaveDeviceInfo: {
               console.log("onSaveDeviceInfo, _deviceId:" + _deviceId)
               console.log("onSaveDeviceInfo, _deviceAddress:" + _deviceAddress)
               console.log("onSaveDeviceInfo, _deviceName:" + _deviceName)
               console.log("onSaveDeviceInfo, _deviceAvatar:" + _deviceAvatar)
               controller.updateDeviceInfo(_deviceId, _deviceAddress, _deviceName, _deviceAvatar)
           }
       }
    }
    Component {
       id: scanningDevices_component
       DeviceScanningView {
       }
    }
}
