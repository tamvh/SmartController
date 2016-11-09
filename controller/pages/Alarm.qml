import QtQuick 2.6
import QtQml 2.2
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
    id: pageDashboard
    title: "Device Detail"
    property var _hour: ""
    property var _minute: ""
    property var _calendarId: -1
    property var _deviceName: ""
    property var _deviceId: ""
    property var _groupname: ""
    property var _power: 0
    property var _actionType: 0
    property var _repeatType: 0
    property var _hourStr: ""
    property var _minuteStr: ""
    property var _totalAlarm: 0
    Settings {
        id: settings
        property string style: "Universal"
    }


    DeviceCalendarController {
        id: deviceCalendarController
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
                color: "white"
            }

            ToolButton {
                Rectangle {
                    id: rectAddAlarm
                    height: parent.height
                    width: parent.width
                    border.color: "white"
                    border.width: 1
                    color: "lightblue"
                    radius: 7
                    anchors {
                        top: parent.top
                        topMargin: 10
                        bottom: parent.bottom
                        bottomMargin: 10
                        left: parent.left
                        leftMargin: 5
                        right: parent.right
                        rightMargin: 10
                    }
                    Text {
                        text: qsTr("+")
                        color: "white"
                        font.pixelSize: 15
                        anchors.centerIn: parent
                    }
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.push("qrc:/pages/SetAlarm.qml", {_calendarId: _calendarId, _deviceId: _deviceId, _deviceName: _deviceName});
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        if(Global.g_deviceName === "") {
            titleLabel.text = _deviceName
        }
        else
        {
            titleLabel.text = Global.g_deviceName
        }

        if(_deviceName === "") {
            _deviceName = titleLabel.text
        }
    }



    Rectangle {
        id: rectIcon
        height: parent.height/3;
        width: parent.width;
        color: "lightblue"

        Timer {
            interval: 1000;
            running: true;
            repeat: true;
            onTriggered: {
                timer.text = new Date().toLocaleTimeString(Qt.locale("de_DE"), "hh:mm:ss") + "";
            }
        }

        Label {
            id: timer
            text: new Date().toLocaleTimeString(Qt.locale("de_DE"), "hh:mm:ss") + "";
            font.pixelSize: 13
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 10
            anchors.horizontalCenter: parent.horizontalCenter
            color: "#FF8A65"
        }

        Rectangle {
            anchors {
                bottom: timer.top
                bottomMargin: 10
                left: parent.left
                right: parent.right
                leftMargin: 40
                rightMargin: 40
            }

            color: "#FAFAFA"
            height: 0.3
        }

        Image {
            id: icoLamp
            source: "qrc:/images/icolight.png"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.verticalCenter: parent.verticalCenter
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    console.log("rectIcon onClicked");
                }
            }
        }



        MouseArea {
            anchors.fill: parent
            onPressed: rectIcon.state = "PRESSED"
            onReleased: rectIcon.state = "RELEASED"
        }

        states: [
            State {
                name: "PRESSED"
                PropertyChanges { target: rectIcon; color: "lightsteelblue"}
                PropertyChanges { target: header; color: "lightsteelblue"}
                PropertyChanges { target: rectAddAlarm; color: "lightsteelblue"}
            },
            State {
                name: "RELEASED"
                PropertyChanges { target: rectIcon; color: "lightblue"}
                PropertyChanges { target: header; color: "lightblue"}
                PropertyChanges { target: rectAddAlarm; color: "lightblue"}
            }
        ]

        transitions: [
            Transition {
                from: "PRESSED"
                to: "RELEASED"
                ColorAnimation { target: rectIcon; duration: 100}
                ColorAnimation { target: header; duration: 100}
                ColorAnimation { target: rectAddAlarm; duration: 100}
            },
            Transition {
                from: "RELEASED"
                to: "PRESSED"
                ColorAnimation { target: rectIcon; duration: 100}
                ColorAnimation { target: header; duration: 100}
                ColorAnimation { target: rectAddAlarm; duration: 100}
            }
        ]
    }

    Rectangle {
        id: rectController
        width: parent.width
        height: (parent.height * 2) / 3
        color: "#F5F5F5"
        anchors {
            top: rectIcon.bottom
        }
        Rectangle {
            id: rectWarning
            width: parent.width
            height: parent.height
            Label {
                id: lblWarning
                anchors.centerIn: parent
                text: "Not found alarm."
                color: "gray"
                font.pixelSize: 12
            }
            Image {
                id: imgWarning
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    bottom: lblWarning.top
                }
                width: 16
                height: 16
                source: "qrc:/images/clock.png"
            }
        }


        ListView {
            id: listView
            currentIndex: -1
            anchors.fill: parent
            clip: true
            displaced: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
            }
            model: deviceCalendarController.calendarList(_deviceId)
            delegate: ItemDelegate {
                width: parent.width
                height: 55
                RowLayout {
                    id: subMenu

                    spacing: 10
                    anchors {
                        fill: parent
                        left: parent.left
                        leftMargin: 20
                    }

                    Label {
                        id: lblTime
                        font.pixelSize: 13
                        horizontalAlignment: Qt.AlignLeft
                    }

                    Rectangle {
                        id: rectLine
                        anchors {
                            left: lblTime.right
                            leftMargin: 10
                        }

                        color: "#E0E0E0"
                        height: 40
                        width: 0.3
                    }
                    GridLayout {
                        anchors {
                            left: rectLine.right
                            leftMargin: 10
                        }
                        id: gridEvent
                        columns: 1

                        Text {
                            id: txtRepeatType
                            font.pixelSize: 13
                        }
                        Text {
                            id: txtAction
                            font.pixelSize: 12
                            color: "gray"
                        }
                    }

                    GridLayout {
                        anchors {
                            right: parent.right
                            rightMargin: 10
                        }
                        columns: 1

                        Switch {
                            id: swSetAlarm
                            checked: true
                        }
                    }

                    Component.onCompleted: {
                        _totalAlarm += 1;
                        if(minute < 10) {
                            _minuteStr = "0" + minute;
                        }
                        else
                        {
                            _minuteStr = minute;
                        }

                        if(hour < 10) {
                            _hourStr = "0" + hour;
                        }
                        else
                        {
                            _hourStr = hour;
                        }
                        lblTime.text = _hourStr + ":" + _minuteStr

                        _actionType = actionType;
                        if(_actionType === 1)
                        {
                            txtAction.text = "Action: Turn Off";
                        }
                        else
                        {
                            txtAction.text = "Action: Turn On";
                        }

                        _repeatType = repeatMode;
                        if(_repeatType == 0) {
                            txtRepeatType.text = "Repeat: <i>never</i>";
                        }
                        if(_repeatType == 1) {
                            txtRepeatType.text = "Repeat: <i>everyday</i>";
                        }
                        if(_repeatType == 2) {
                            txtRepeatType.text = "Repeat: <i>Mon to Fri</i>";
                        }
                        if(_repeatType == 3) {
                            txtRepeatType.text = "Repeat: <i>" + repeartText + "</i>";
                        }
                    }

                }
                Rectangle {
                    anchors {
                        left: parent.left
                        right: parent.right
                        leftMargin: 20
                    }

                    color: "#E0E0E0"
                    height: 0.3
                }

                highlighted: ListView.isCurrentItem
                onPressAndHold: {
                    console.log("open popup");
                    if(hour < 10) {
                        _hour = "0" + hour;
                    } else {
                        _hour = hour;
                    }

                    if(minute < 10) {
                        _minute = "0" + minute;
                    } else {
                        _minute = minute;
                    }

                    _calendarId = calendarId;
                    popupDeleteAlarm.open();
                }

            }

        }

        Component.onCompleted: {
            if(_totalAlarm > 0) {
                rectWarning.visible = false;
                listView.visible = true;
            }
            else
            {
                rectWarning.visible = true;
                listView.visible = false;
            }
        }
    }

    Popup {
        id: popupDeleteAlarm
        x: 0
        y: parent.height - height
        width: parent.width
        height: 160
        modal: true
        focus: true

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"
        }

        Item {
            height: parent.height
            width: parent.width

            Label {
                id: txtTitleDeleteAlarm
                anchors.horizontalCenter: parent.horizontalCenter
                text: "[" + _hour + ":" + _minute + "]"
                color: "#EF6C00"
            }

            Rectangle {
                id: rectDeleteOK
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                anchors {
                    top: txtTitleDeleteAlarm.bottom
                    topMargin: 10
                }


                Text {
                    id: btnDeleteOK
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Delete")
                    font.pixelSize: 12
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        deviceCalendarController.removeCalendar(_calendarId);
                        popupDeleteAlarm.close();
                        _totalAlarm -= 1;
                        if(_totalAlarm > 0) {
                            lblWarning.visible = false;
                            listView.visible = true;
                        }
                        else
                        {
                            lblWarning.visible = true;
                            listView.visible = false;
                        }
                    }
                }
            }

            Rectangle {
                id: rectDeleteCancel
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                anchors {
                    top: rectDeleteOK.bottom
                    topMargin: 10

                }


                Text {
                    id: btnDeleteCancel
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Cancel")
                    font.pixelSize: 12
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popupDeleteAlarm.close();                        
                    }
                }
            }
        }
    }


}
