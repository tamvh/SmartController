import QtQuick 2.6
import QtQml 2.2
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import QtQuick.Extras 1.4
import SmartControls 1.0
import "Common.js" as Global

Page {
    id: pageSetLamp
    title: "Set alarm"
    Settings {
        id: settings
        property string style: "Universal"
    }

    readonly property var _hours: ["00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10",
        "11", "12", "13", "14", "15", "16", "17", "18", "19", "20",
        "21", "22", "23"]
    readonly property var _minutes: ["00", "01", "02", "03", "04", "05", "06", "07", "08", "09", 10,
        11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
        21, 22, 23 ,24, 25, 26, 27, 28, 29, 30,
        31, 32, 33, 34, 35, 36, 37, 38, 39, 40,
        41, 42, 43, 44, 45, 46, 47, 48, 49, 50,
        51, 52, 53, 54, 55, 56, 57, 58, 59]
    property var _hvalue: 0
    property var _mvalue: 0
    property var _repeartType: 0
    property var _repeartItems: []
    property var _actionType: -1
    property var _deviceId: ""
    property var _deviceName: ""
    property var _calendarId: -1
    property var _autoOn: false

    property var _valMon: ""
    property var _valTue: ""
    property var _valWed: ""
    property var _valThu: ""
    property var _valFri: ""
    property var _valSat: ""
    property var _valSun: ""

    DeviceCalendarController {
        id: deviceCalendarController
    }

    background: Rectangle {
        implicitWidth: Screen.width
        implicitHeight: Screen.height
        color: "#EEEEEE"
    }

    header:ToolBar {
        background: Rectangle {
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
                text: title
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            ToolButton {
                Rectangle {
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
                        leftMargin: 10
                        right: parent.right
                        rightMargin: 5
                    }
                    Text {
                        text: qsTr("OK")
                        color: "white"
                        font.pixelSize: 10
                        anchors.centerIn: parent
                    }
                }

                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("------ADD ALARM------");
                        console.log("_deviceId: " + _deviceId);
                        console.log("_hvalue: " + _hvalue);
                        console.log("_mvalue: " + _mvalue);
                        console.log("_repeartType: " + _repeartType);
                        console.log("_actionType: " + _actionType);
                        console.log("_repeartItems: " + _repeartItems);
                        deviceCalendarController.insertDeviceCalendar(
                                                             _deviceId,
                                                             _hvalue,
                                                             _mvalue,
                                                             _repeartType,
                                                             _actionType,
                                                             _repeartItems,
                                                             _autoOn);
                        Global.g_deviceName = _deviceName;
                        Global.g_deviceId = _deviceId;
                        stackView.pop();
                        stackView.replace("qrc:/pages/Alarm.qml", StackView.PushTransition, {_deviceName: _deviceName, _deviceId: _deviceId});
//                            stackView.replace("qrc:/pages/Alarm.qml", StackView.PushTransition);
                    }
                }
            }
        }
    }

    Column {
        anchors.fill: parent
        Rectangle {
            id: rectRepeat
            height: 55
            width: parent.width
            color: "#EEEEEE"


            GridLayout {
                width: parent.width - 60
                height: 55
                columns: 1
                anchors {
                    left: parent.left
                    leftMargin: 20
                }
                RowLayout {
                    Text {
                        text: "Repeat";
                        font.pixelSize: 13
                    }
                }

                RowLayout {
                    Text {
                        id: lblAlarm
                        text: "Never";
                        font.pixelSize: 12
                        color: "gray"
                        font.italic: true
                    }
                }
            }

            GridLayout {
                width: 55
                height: 55
                columns: 1
                anchors {
                    right: parent.right
                    rightMargin: 10
                }

                ToolButton {
                    Image {
                        id: imgRepeat
                        anchors.centerIn: parent
                        height: 16
                        width: 16
                        source: "qrc:/images/repeat.png"
                    }
                    ColorOverlay {
                        anchors.fill: imgRepeat
                        source: imgRepeat
                        color: "gray"
                    }
                }
            }




            MouseArea {
                anchors.fill: parent
                onPressed: {
                    rectRepeat.color = "#FFF3E0"
                }
                onClicked: {
                    rectRepeat.color = "#EEEEEE"
                    popupSelectRepeat.open()
                }
            }
        }
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }

            color: "#BDBDBD"
            height: 0.3
        }
        Rectangle {
            id: rectRingTone
            height: 55
            width: parent.width
            color: "#EEEEEE"

            GridLayout {
                width: parent.width - 60
                height: 55
                columns: 1
                anchors {
                    left: parent.left
                    leftMargin: 20
                }
                RowLayout {
                    Text {
                        text: "Ring tone";
                        font.pixelSize: 13

                    }
                }

                RowLayout {
                    Text {
                        text: "Default ringtone";
                        font.pixelSize: 12
                        color: "gray"
                        font.italic: true
                    }
                }
            }

            GridLayout {
                id: gridImg
                width: 55
                height: 55
                columns: 1
                anchors {
                    right: parent.right
                    rightMargin: 10
                }

                ToolButton {
                    Image {
                        anchors.centerIn: parent
                        id: imgRington
                        height: 16
                        width: 16
                        source: "qrc:/images/notification.png"
                    }
                    ColorOverlay {
                        anchors.fill: imgRington
                        source: imgRington
                        color: "gray"
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    rectRingTone.color = "#FFF3E0"
                }
                onClicked: {
                    rectRingTone.color = "#EEEEEE"
                }
            }
        }

        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }

            color: "#BDBDBD"
            height: 0.3
        }
        Rectangle {
            id: rectVibrate
            height: 55
            width: parent.width
            color: "#EEEEEE"

            GridLayout {
                width: parent.width - 60
                height: 55
                columns: 1
                anchors {
                    left: parent.left
                    leftMargin: 20
                }
                RowLayout {
                    Text {
                        text: "Vibrate when alarm sounds";
                        font.pixelSize: 13

                    }
                }

            }

            GridLayout {
                width: 55
                height: 55
                columns: 1
                anchors {
                    right: parent.right
                    rightMargin: 10
                }

                ToolButton {
                    Switch {
                        id: swVibrate
                        anchors.centerIn: parent                        
                        checked: true
                    }
                }
            }

            MouseArea {
                anchors.fill: parent
                onPressed: {
                    rectVibrate.color = "#FFF3E0"
                }
                onClicked: {
                    rectVibrate.color = "#EEEEEE"
                    if(swVibrate.checked === true)
                    {
                        swVibrate.checked=false;
                    }
                    else
                    {
                        swVibrate.checked=true;
                    }
                }
            }
        }
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }

            color: "#BDBDBD"
            height: 0.3
        }


        Rectangle {
            id: rectAction
            height: 55
            width: parent.width
            color: "#EEEEEE"


            GridLayout {
                width: parent.width - 60
                height: 55
                columns: 1
                anchors {
                    left: parent.left
                    leftMargin: 20
                }
                RowLayout {
                    Text {
                        text: "Action";
                        font.pixelSize: 13
                    }
                }

                RowLayout {
                    Text {
                        id: lblActionValue
                        text: "Turn on";
                        font.pixelSize: 12
                        color: "gray"
                        font.italic: true
                    }
                }
            }

            GridLayout {
                width: 55
                height: 55
                columns: 1
                anchors {
                    right: parent.right
                    rightMargin: 10
                }

                ToolButton {
                    Switch {
                        id: swAction
                        anchors.centerIn: parent
                        checked: true
                    }
                }
            }




            MouseArea {
                anchors.fill: parent
                onPressed: {
                    rectAction.color = "#FFF3E0"
                }
                onClicked: {
                    rectAction.color = "#EEEEEE"
                    if(swAction.checked === true)
                    {
                        swAction.checked=false;
                        _actionType = 1;
                        lblActionValue.text = "Turn off";
                    }
                    else
                    {
                        swAction.checked=true;
                        _actionType = 0;
                        lblActionValue.text = "Turn on";
                    }
                }
            }
        }
        Rectangle {
            anchors {
                left: parent.left
                right: parent.right
            }

            color: "#BDBDBD"
            height: 0.3
        }




        Rectangle {
            id: rectTumbler
            height: parent.height
            width: parent.width
            color: "#EEEEEE"

            GridLayout {
                width: parent.width
                height: parent.height/1.5
                columns: 1
                anchors {
                    left: parent.left
                    leftMargin: 20
                    right: parent.right
                    rightMargin: 20
                }

                RowLayout {
                    anchors.centerIn: parent
                    width: parent.width
                    height: parent.height
                    Text {
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            bottom: tumbler.top
                            bottomMargin: 10
                        }
                        id: txtTime
                        text: "00:00";
                        font.bold: true
                        font.pixelSize: 20
                        color: "gray"

                    }
                    Tumbler {
                        id: tumbler
                        anchors.centerIn: parent                        
                        TumblerColumn {
                            id: tumHour
                            model: _hours

                            onCurrentIndexChanged: {                                
                                if(currentIndex <10)
                                {
                                    _hvalue = "0" + currentIndex;
                                }
                                else
                                {
                                    _hvalue = currentIndex;
                                }
                                txtTime.text = _hvalue + ":" +  _mvalue

                                console.log("_hvalue: " + _hvalue);
                            }
                        }
                        TumblerColumn {
                            id: tumMinute
                            model: _minutes
                            onCurrentIndexChanged: {
                                if(currentIndex <10)
                                {
                                    _mvalue = "0" + currentIndex;
                                }
                                else
                                {
                                    _mvalue = currentIndex;
                                }
                                txtTime.text = _hvalue + ":" +  _mvalue

                                console.log("_mvalue: " + _mvalue);
                            }
                        }
                        Component.onCompleted: {
                            tumbler.setCurrentIndexAt(0, new Date().toLocaleTimeString(Qt.locale("de_DE"), "hh") + ""); // current hour
                            tumbler.setCurrentIndexAt(1, new Date().toLocaleTimeString(Qt.locale("de_DE"), "mm") + ""); // current minute
                        }
                    }               
                }
            }
        }
    }

    Popup {
        id: popupSelectRepeat
        x: 5
        y: parent.height - height -5
        width: parent.width - 10
        height: 270
        modal: true
        focus: true
        background: Rectangle {
            radius: 5
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"
            border.color: "#FFCCBC"
            border.width: 0.3
        }

        Item {
            height: parent.height
            width: parent.width

            Rectangle {
                id: rectOne
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                color: "white"
                anchors {
                    top: parent.top
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("One time (Never repeat)")
                    font.pixelSize: 12
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        lblAlarm.text = "Never";
                        _repeartType = 0;
                        popupSelectRepeat.close();
                    }
                }
            }

            Rectangle {
                id: rectEveryday
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                color: "white"
                anchors {
                    top: rectOne.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Every day")
                    font.pixelSize: 12
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        lblAlarm.text = "Every day";
                        _repeartType = 1;
                        popupSelectRepeat.close();
                    }
                }
            }

            Rectangle {
                id: rectSelectday
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                color: "white"
                anchors {
                    top: rectEveryday.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Mon Tue Wed Thus Fri")
                    font.pixelSize: 12
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        lblAlarm.text = "Mon Tue Wed Thu Fri"
                        _repeartType = 2;
                        popupSelectRepeat.close();
                    }
                }
            }

            Rectangle {
                id: rectCustom
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                color: "white"
                anchors {
                    top: rectSelectday.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Custom")
                    font.pixelSize: 12
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        popupSelectRepeat.close()
                        lblAlarm.text = "Custom";
                        _repeartType = 3;
                        popupCustom.open();
                    }
                }
            }
        }
    }

    //--------------popup custom

    Popup {
        id: popupCustom
        x: 5
        y: parent.height - height -5
        width: parent.width - 10
        height: 550
        modal: true
        focus: true
        background: Rectangle {
            radius: 5
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"
            border.color: "#FFCCBC"
            border.width: 0.3
        }

        Item {
            height: parent.height
            width: parent.width

            Rectangle {
                id: rectRepeatStr
                width: parent.width
                height: 40

                anchors {
                    top: parent.top
                    topMargin: 10
                }

                Text {
                    id: txtRepeatStr
                    font.pixelSize: 12
                    text: _valMon + " " + _valTue + " " + _valWed + " " + _valThu + " " + _valFri + " " + _valSat + " " + _valSun
                    color: "red"
                    anchors {
                        centerIn: parent
                    }
                }
            }

            Rectangle {
                id: rectMon
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectRepeatStr.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Moday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkMon
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgMon
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgMon
                        source: imgMon
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkMon.visible)
                        {
                            _valMon = "";
                            chkMon.visible = false;
                            rectMon.color = "white";
                            chkMon.color = "white"
                            _repeartItems.pop("Mon");
                        }
                        else
                        {
                            _valMon = "Mon";
                            chkMon.visible = true;
                            chkMon.color = "#EEEEEE"
                            rectMon.color = "#EEEEEE";
                            _repeartItems.push("Mon");
                        }
                    }
                }
            }


            Rectangle {
                id: rectTue
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectMon.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Tueday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkTue
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgTue
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgTue
                        source: imgTue
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkTue.visible)
                        {
                            _valTue = "";
                            chkTue.visible = false;
                            rectTue.color = "white";
                            chkTue.color = "white"
                            _repeartItems.pop("Tue");
                        }
                        else
                        {
                            _valTue = "Tue";
                            chkTue.visible = true;
                            chkTue.color = "#EEEEEE"
                            rectTue.color = "#EEEEEE";
                            _repeartItems.push("Tue");
                        }
                    }
                }
            }


            Rectangle {
                id: rectWed
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectTue.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Wednesday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkWed
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgWed
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgWed
                        source: imgWed
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkWed.visible)
                        {
                            _valWed = "";
                            chkWed.visible = false;
                            rectWed.color = "white";
                            chkWed.color = "white"
                            _repeartItems.pop("Wed");
                        }
                        else
                        {
                            _valWed = "Wed";
                            chkWed.visible = true;
                            chkWed.color = "#EEEEEE"
                            rectWed.color = "#EEEEEE";
                            _repeartItems.push("Wed");
                        }
                    }
                }
            }



            Rectangle {
                id: rectThu
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectWed.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Thusday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkThu
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgThu
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgThu
                        source: imgThu
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkThu.visible)
                        {
                            _valThu = "";
                            chkThu.visible = false;
                            rectThu.color = "white";
                            chkThu.color = "white"
                            _repeartItems.pop("Thu");
                        }
                        else
                        {
                            _valThu = "Thu";
                            chkThu.visible = true;
                            chkThu.color = "#EEEEEE"
                            rectThu.color = "#EEEEEE";
                            _repeartItems.push("Thu");
                        }
                    }
                }
            }


            Rectangle {
                id: rectFri
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectThu.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Friday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkFri
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgFri
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgFri
                        source: imgFri
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkFri.visible)
                        {
                            _valFri = "";
                            chkFri.visible = false;
                            rectFri.color = "white";
                            chkFri.color = "white"
                            _repeartItems.pop("Fri");
                        }
                        else
                        {
                            _valFri = "Fri";
                            chkFri.visible = true;
                            chkFri.color = "#EEEEEE"
                            rectFri.color = "#EEEEEE";
                            _repeartItems.push("Fri");
                        }
                    }
                }
            }


            Rectangle {
                id: rectSat
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectFri.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Saturday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkSat
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgSat
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgSat
                        source: imgSat
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkSat.visible)
                        {
                            _valSat = "";
                            chkSat.visible = false;
                            rectSat.color = "white";
                            chkSat.color = "white"
                            _repeartItems.pop("Sat");
                        }
                        else
                        {
                            _valSat = "Sat";
                            chkSat.visible = true;
                            chkSat.color = "#EEEEEE"
                            rectSat.color = "#EEEEEE";
                            _repeartItems.push("Sat");
                        }
                    }
                }
            }



            Rectangle {
                id: rectSun
                width: parent.width
                height: 45
                border.color: "#EEEEEE"
                border.width: 0.5
                color: "white"
                radius: 45
                anchors {
                    top: rectSat.bottom
                    topMargin: 10
                }

                Text {
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Sunday")
                    font.pixelSize: 12
                }
                Rectangle
                {
                    id: chkSun
                    height: 16
                    width: 16
                    anchors {
                        right: parent.right
                        rightMargin: 20
                    }
                    Image {
                        id: imgSun
                        height: 16
                        width: 16
                        source: "qrc:/images/check.png"
                        anchors.centerIn: parent
                        opacity: 1.0
                    }

                    ColorOverlay {
                        anchors.fill: imgSun
                        source: imgSun
                        color: "#00C853"
                    }
                    visible: false
                }


                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        if(chkSun.visible)
                        {
                            _valSun = "";
                            chkSun.visible = false;
                            rectSun.color = "white";
                            chkSun.color = "white"
                            _repeartItems.pop("Sun");
                        }
                        else
                        {
                            _valSun = "Sun";
                            chkSun.visible = true;
                            chkSun.color = "#EEEEEE"
                            rectSun.color = "#EEEEEE";
                            _repeartItems.push("Sun");
                        }
                    }
                }
            }


            Rectangle {
                id: rectConfirm
                width: parent.width
                height: 45
                color: "white"
                anchors {
                    top: rectSun.bottom
                    topMargin: 30
                }

                Rectangle {
                    id: rectOK
                    height: 45
                    width: parent.width/2 - 5
                    border.color: "#EEEEEE"
                    border.width: 0.5
                    color: "#D7CCC8"
                    radius: 10
                    Text {
                        text: qsTr("OK")
                        anchors.centerIn: parent
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            if(txtRepeatStr.text.trim() === "")
                            {
                                lblAlarm.text = "Never";
                                _repeartType = 0;
                            }
                            else
                            {
                                lblAlarm.text = txtRepeatStr.text.trim();
                                _repeartType = 3;
                            }

                            popupCustom.close();
                        }
                    }
                }
                Rectangle {
                    id: rectCancel
                    height: 45
                    width: parent.width/2 - 5
                    border.color: "#EEEEEE"
                    border.width: 0.5
                    color: "#D7CCC8"
                    radius: 10
                    Text {
                        text: qsTr("Cancel")
                        anchors.centerIn: parent
                    }
                    anchors {
                        right: parent.right
                        rightMargin: 0
                    }

                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            lblAlarm.text = "Never";
                            _repeartType = 0;
                            popupCustom.close();
                        }
                    }
                }

            }
        }
    }
}






















