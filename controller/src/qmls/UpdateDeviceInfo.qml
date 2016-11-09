import QtQuick 2.0
import QtQuick.Controls 1.1
import QtQuick.Controls.Styles 1.1
import Material 0.2

Page {
    property int _deviceId: -1
    property var _deviceAddress: ""
    property var _deviceName: ""
    property var _deviceAvatar: "plug"

    title : "Sửa thông tin công tắc"

    actions: [
        Action {
            iconName: "action/delete"
            onTriggered: {
                console.debug("delete device");
            }
        }

    ]
    signal saveDeviceInfo(int deviceId, var deviceAddress, var devicename, var deviceAvatar)

    Column {
        id: deviceNameLayout
        anchors {
            top: parent.top
            topMargin: Units.dp(20)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }
        spacing: 0

        Text {
            id: name
            height: Units.dp(28)
            text: qsTr("Tên công tắc")
        }

        TextField {
            id: edtDeviceName
            height: Units.dp(48)
            width: parent.width
            verticalAlignment: TextInput.AlignVCenter
            placeholderText: "Công tắc phòng khách"
            font { pixelSize: Units.dp(16); }
            style: TextFieldStyle {
                textColor: "black"
                placeholderTextColor: CSS.colorSilver
            }
            text: _deviceName
            onTextChanged:  {
                _deviceName = edtDeviceName.text
            }
        }
    }

    Column {
        anchors {
            top: deviceNameLayout.bottom
            topMargin: Units.dp(20)
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
        }
        spacing: Units.dp(0)

        Text {
            height: Units.dp(40)
            text: qsTr("Chọn hình đại diện")
        }

        Row {
            spacing: Units.dp(20)

            Rectangle {
                width: Units.dp(80)
                height: Units.dp(80)
                color: _deviceAvatar=="lamp"?CSS.colorGreenSea:"transparent"
                radius: Units.dp(10)

                Rectangle {
                    width: Units.dp(76)
                    height: Units.dp(76)
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                    radius: Units.dp(10)
                }

                Icon {
                    width: Units.dp(60)
                    height: Units.dp(60)
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }

                    name: "action/lock_outline"
                    color: "#6c6c6c"
                    size: Units.dp(60)
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        _deviceAvatar = "lamp"
                    }
                }
            }

            Rectangle {
                width: Units.dp(80)
                height: Units.dp(80)
                color: _deviceAvatar=="plug"?CSS.colorGreenSea:"transparent"
                radius: Units.dp(10)

                Rectangle {
                    width: Units.dp(76)
                    height: Units.dp(76)
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                    radius: Units.dp(10)
                }

                Icon {
                    width: Units.dp(60)
                    height: Units.dp(60)
                    anchors {
                        horizontalCenter: parent.horizontalCenter
                        verticalCenter: parent.verticalCenter
                    }
                    name: "action/lock_open"
                    color: "#6c6c6c"
                    size: Units.dp(60)
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        _deviceAvatar = "plug"
                    }
                }
            }
        }
    }

    Button {
        id: button
        height: Units.dp(48)
        elevation: 1
        backgroundColor: "#ffa726"

        anchors {
            left: parent.left
            leftMargin: Units.dp(10)
            right: parent.right
            rightMargin: Units.dp(10)
            bottom: parent.bottom
            bottomMargin: Units.dp(10)
        }

        text: "Lưu thông tin"

        onClicked: {
            saveDeviceInfo(_deviceId, _deviceAddress, _deviceName, _deviceAvatar)
            pop(null, true);
        }
    }
}

