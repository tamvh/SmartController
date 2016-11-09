import QtQuick 2.0
import QmlControls 0.1
import QtQuick.Layouts 1.1
import Material 0.2 as Material
import Material.ListItems 0.1 as ListItem
import QtQuick.Controls 1.3 as QuickControls
import QtQuick.Controls.Styles 1.0
import SmartControls 1.0

Material.Page {
    property DeviceCalendarController controller
    property int _calendarId: -1
    signal saveAlarm(int calendarId,int hour, int minute,int repeartMode, bool autoOn);

    property var _index: -1;
    property int alarmHour: -1;
    property int alarmMinute: -1;
    property int alarmRepeatMode: 0; //0: once; 1: everyDay; 2: Mon to Fri; 3: Custom
    property int _repeatItem: 0;
    property bool alarmAutoOn: true


    Component.onCompleted: {
        alarmHour = alarmHour<=0?7:alarmHour
        alarmMinute = alarmMinute<=0?0:alarmMinute
        timePicker._hour = alarmHour
        timePicker._minute = alarmMinute
        timeButton.text = convertTime(alarmHour, alarmMinute)
    }

    title : "Hẹn giờ bật/tắt"

    onAlarmAutoOnChanged: {
        autoOnComboBox.currentIndex = alarmAutoOn? 0:1
    }
    onAlarmRepeatModeChanged: {
        repeartComboBox.currentIndex = alarmRepeatMode
    }

    MouseArea {
        anchors.fill: parent
        onClicked:  {
            timePicker.visible = false
        }
    }

    Column {
        anchors {
            top: parent.top
            topMargin: Unit.dp(0)
            left: parent.left
            leftMargin: Unit.dp(10)
        }
        width: parent.width
        spacing: Unit.dp(5)

        Row {
            height: Unit.dp(80)
            spacing: Unit.dp(10)
            FontImage {
                id: icon
                width: Unit.dp(70)
                height: Unit.dp(70)
                anchors {
                    verticalCenter: parent.verticalCenter
                }
                source: controller.deviceAvatar
                color: "#0A3D91"
                iconSize: 70
            }
            Text {
                height: parent.height
                text: controller.deviceName
                font.family: "Times New Roman"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pointSize: 16
                color: "#009788"
            }
        }
        Item {
            anchors {
                left: parent.left
                right: parent.right
            }
            height: Unit.dp(40)
            Material.Label {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                text: "Tự động"
                style: {
                    font: Unit.sp(16)
                    color: "black"
                }
            }

            QuickControls.ComboBox {
                id: autoOnComboBox
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: Unit.dp(20)
                }
                width: Unit.dp(120)
                height: Unit.dp(40)
                model: ListModel {
                    ListElement { text: "Bật"}
                    ListElement { text: "Tắt"}
                }
                style: ComboBoxStyle {
                    background: Material.Button {
                        width: autoOnComboBox.width
                        height: autoOnComboBox.height
                        elevation: 1
                    }
                }
            }
        }
        Item {
            width: parent.width
            height: Unit.dp(40)
            Material.Label {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                text: "Lặp lại"
                style: {
                    font: Unit.sp(16)
                    color: "black"
                }
            }
            QuickControls.ComboBox {
                id: repeartComboBox
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: Unit.dp(20)
                }
                width: Unit.dp(120)
                height: Unit.dp(40)

                model: ListModel {
                    ListElement { text: "Một lần"}
                    ListElement { text: "Hàng ngày"}
                }
                style: ComboBoxStyle {
                    background: Material.Button {
                        width: repeartComboBox.width
                        height: repeartComboBox.height
                        elevation: 1
                    }
                }
            }
        }
        Item {
            width: parent.width
            height: Unit.dp(40)
            Material.Label {
                anchors {
                    left: parent.left
                    verticalCenter: parent.verticalCenter
                }
                text: "Thời gian"
                style: {
                    font: Unit.sp(16)
                    color: "black"
                }
            }
            Material.Button {
                id: timeButton
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                    rightMargin: Unit.dp(20)
                }
                width: Unit.dp(120)
                height: Unit.dp(40)
                elevation: 1
                backgroundColor: "white"
                text: "10:00 PM"
                onClicked:  {
                    timePicker.visible = true

                }
            }
        }
    }
    onSaveAlarm: {
        controller.updateDeviceCalendar(calendarId,
                                        hour,
                                        minute,
                                        repeartMode,
                                        autoOn)
    }
    Material.Button {
        width: parent.width
        height: Unit.dp(50)
        anchors.bottom: parent.bottom
        backgroundColor: CSS.colorGreenSea
        onClicked:  {
            saveAlarm(_calendarId, alarmHour, alarmMinute, repeartComboBox.currentIndex, (autoOnComboBox.currentIndex == 0))
            pop()
        }
        Rectangle {
            anchors.fill: parent
            color: "transparent"
            Text {
                id: btnText
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                text: _calendarId == -1?"Thêm hẹn giờ":"Lưu"
                color: "white"
                font.pixelSize: Unit.sp(16)
            }

            Button {
                width: Unit.dp(48)
                height: Unit.dp(48)
                anchors {
                    right: btnText.left
                    rightMargin: Unit.dp(0)
                }
                iconName: _calendarId == -1?"add":"save"
                iconSize: 24
                iconColor: "white"
            }
        }
    }
    TimePicker {
        id:timePicker
        visible: false
        anchors {
            bottom: parent.bottom
            topMargin: Unit.dp(4)
        }

        onSelectedTimeChanged: {
            alarmHour = hour
            alarmMinute = minute
            timeButton.text = convertTime(hour, minute)
        }
    }

    function convertTime( hour, minute) {
        var timeText;
        var type;
        var hourStr;
        var minuteStr;
        if (hour < 12) {
            type = "AM";
            hourStr = hour;
        } else {
            type = "PM";
            hourStr = hour != 12?hour-12:hour;
        }
        minuteStr = minute
        if (hourStr.toString().length<2) {
           hourStr = "0" + hourStr;
        }
        if (minuteStr.toString().length<2) {
           minuteStr = "0" + minuteStr;
        }
        timeText = hourStr + ":" + minuteStr + " " + type;
        console.log("____________:" + timeText)
        return timeText
    }

    QtObject {
        id: internal
        property int hour
        property int minute
        property point time
    }
}

