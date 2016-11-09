import QtQuick 2.0
import Material 0.2 as Material
import SmartControls 1.0

// Hiển thị trang thông tin lịch hẹn giờ của thiết bị
Material.Page {
    property alias deviceId: controller.deviceId
    title: "Hẹn giờ BẬT/TẮT"

    DeviceCalendarController {
        id: controller
    }

    Item {
        id: deviceInfo
        width: parent.width
        height: Material.Units.dp(100)

        Material.Icon {
            id: icon
            width: Material.Units.dp(70)
            height: Material.Units.dp(70)
            anchors {
                left: parent.left
                leftMargin: Material.Units.dp(10)
                verticalCenter: parent.verticalCenter
            }
            name: "device/bluetooth"
            size: Material.Units.dp(48)
        }

        Text {
            anchors {
                left: icon.right
                leftMargin: Material.Units.dp(10)
                right: parent.right
                rightMargin: Material.Units.dp(10)
                verticalCenter: icon.verticalCenter
            }

            text: controller.deviceName
            font.bold: controller.deviceState===1?true:false
            font {
                pixelSize: Material.Units.dp(16)
            }
            height: Material.Units.dp(25)
            width: parent.width
        }
        Item {
            id: bottomItem
            anchors {
                left: icon.right
                leftMargin: Material.Units.dp(10)
                right: parent.right
                rightMargin: Material.Units.dp(5)
                bottom: parent.bottom
            }
            height: Material.Units.dp(30)
        }

        Material.ThinDivider {
            anchors.bottom: parent.bottom
        }
    }
    Item {
        id: bottomPanel
        width: parent.width
        height: Material.Units.dp(50)
        anchors.bottom: parent.bottom

        Material.Button {
            anchors.fill: parent
            backgroundColor: CSS.colorGreenSea
            onClicked:  {
                push(chooseAlarm_component, {
                                controller:controller
                                })
            }

            text: "Thêm hẹn giờ"
        }
    }
    ListView {
        id: calendarListView
        anchors {
            top: deviceInfo.bottom
            bottom: bottomPanel.top
            left: parent.left
            right: parent.right
        }
        clip: true
        model: controller.calendarList
        delegate: DeviceCalendarItem {
            onDeleteButtonClicked:  {
                console.info("row: ",row, "calendarId", calendarId)
                controller.deleteDeviceCalendar(row, calendarId )
            }
            onEditButtonClicked: {
                push(chooseAlarm_component, {
                                controller: controller,
                                _calendarId: calendarId,
                                alarmHour: hour,
                                alarmMinute: minute,
                                alarmRepeatMode: repeatMode,
                                alarmAutoOn: autoOn
                                })
            }
        }
    }
    Component {
        id: chooseAlarm_component
        ChooseAlarm {}
    }
}
