import QtQuick 2.0
import QmlControls 0.1 as QmlControls
import QmlItem 0.1 as QmlItem
import Material 0.2 as Material
import SmartControls 1.0

Material.Page {
    title: "Tìm kiếm thiết bị"

    property string _suggestSearch: "Để thêm thiết bị, bạn bấm nút Tìm kiếm phía dưới"
    property string _deviceInvalid: "Không phải là thiết bị hợp lệ"

    DeviceScanningController {
        id: controller
    }

    onGoBack: {
        if (controller.scanningState == 1) {
            controller.stopScanDevices()
        }
    }

    ListView {
        id: deviceListView
        anchors {
            top: parent.top
            bottom: scanButton.top
            left: parent.left
            right: parent.right
        }
        clip: true
        model: controller.deviceList
        delegate: scanningItemDelegate
    }

    Material.Button {
        id: scanButton
        height: Material.Units.dp(48)
        elevation: 1
        backgroundColor: "#EF6C00"
        anchors {
            left: parent.left
            leftMargin: Material.Units.dp(10)
            right: parent.right
            rightMargin: Material.Units.dp(10)
            bottom: parent.bottom
            bottomMargin: Material.Units.dp(10)
        }

        onClicked: {
            console.log("onClicked Turn on")
            if (controller.scanningState == 0) {
                controller.startScanDevices()
            } else {
                controller.stopScanDevices()
            }
        }

        Material.ProgressCircle {
            id:progress
            visible: controller.scanningState == 1
            width: Material.Units.dp(30)
            height: Material.Units.dp(30)
            anchors {
                right: buttonTitle.left
                rightMargin: Material.Units.dp(10)
                verticalCenter: parent.verticalCenter
            }
            color: "#ffffff"
        }
        Material.Icon {
            id: icon
            visible: controller.scanningState == 0
            width: Material.Units.dp(30)
            height: Material.Units.dp(30)
            anchors {
                right: buttonTitle.left
                rightMargin: Material.Units.dp(10)
                verticalCenter: parent.verticalCenter
            }
            name: "action/search"
            color: "#ffffff"
            size: Material.Units.dp(30)
        }
        Text {
            id: buttonTitle
            text: controller.scanningState == 0?"TÌM KIẾM":"TẠM DỪNG"
            font.family: "Helvetica"
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: "white"
        }
    }

    Text {
        id: txtSuggestSearch
        anchors {
            left: parent.left
            leftMargin: Material.Units.dp(10)
            right: parent.right
            rightMargin: Material.Units.dp(10)
            bottom: scanButton.top
            bottomMargin: Material.Units.dp(10)
        }
        visible: controller.scanningState == 0
        wrapMode: Text.WordWrap
        clip: true
        horizontalAlignment: Text.AlignHCenter
        text: qsTr(_suggestSearch)
    }

    Material.Snackbar {
        id: snackbar
        anchors {
            bottom: txtSuggestSearch.top
        }
    }

    Component {
        id: scanningItemDelegate
        Item {
            width: parent.width
            height: Material.Units.dp(90)
            Material.Icon {
                id: icon
                width: Material.Units.dp(60)
                height: Material.Units.dp(60)
                anchors {
                    left: parent.left
                    leftMargin: Material.Units.dp(10)
                    verticalCenter: parent.verticalCenter
                }
                name: "device/bluetooth"
                color: "#0A3D91"
                size: Material.Units.dp(70)
            }

            Item {
                id: rightItem
                visible: hasLampService ? true : false
                anchors {
                    top: parent.top
                    topMargin: Material.Units.dp(10)
                    right: parent.right
                    rightMargin: Material.Units.dp(10)
                    bottom: parent.bottom
                    bottomMargin: Material.Units.dp(10)
                }

                width: Material.Units.dp(48)
            }

            Column {
                id: deviceInfo
                anchors {
                    left: icon.right
                    leftMargin: Material.Units.dp(10)
                    right: rightItem.right
                    rightMargin: Material.Units.dp(10)
                    top: parent.top
                    topMargin: Material.Units.dp(10)
                }
                spacing: Material.Units.dp(5)
                Text {
                    text: deviceName
                    font {
                        pixelSize: Material.Units.dp(16)
                        family: "Helvetica"
                    }
                    color: "#485C68"
                    height: Material.Units.dp(25)
                    width: parent.width
                }
                Text {
                    height: Material.Units.dp(25)
                    width: parent.width
                    text: deviceAddress
                    font {
                        pixelSize: Material.Units.dp(14)
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
                    controller.selectDevice(deviceAddress);
                    pop(null, true);
                }
            }

            Material.ThinDivider {
                anchors.bottom: parent.bottom
            }
        }
    }
}
