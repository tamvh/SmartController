import QtQuick 2.0
import QmlControls 0.1
/*

Usage:
    DatePicker {
        id: datePicker

        anchors {
            top: parent.top
            horizontalCenter: parent.horizontalCenter
        }

        platformStyle: DatePickerStyle {
            orientationString: datePicker.orientationString()
        }
    }

    You can use
    function setDate(currentDate) for set current selected date and
    function setEvent(eventDate, enable) for set/unset event marker (NB: Markers ca be sets only for selected mounth now)

    Also component emit signal selectedTimeChanged(date selectedDate) when selected date is change
*/

Item {
    id: root
    width: parent.width
    height: Unit.dp(200)

    property int _hour: 0
    property int _minute: 0
//    property DatePickerStyle platformStyle: DatePickerStyle {}

    signal selectedTimeChanged(int hour, int minute);


    QtObject {
        id: internal
        property int hour:_hour
        property int minute:_minute

        property ListModel hourModel: ListModel {}
        property ListModel minuteModel: ListModel {}

        function padDigits(number, digits) {
            return new Array(Math.max(digits - String(number).length + 1, 0)).join(0) + number;
        }

        property point selectedTime
        function update() {
            var newTime = Qt.point(hour, minute);
            selectedTime = newTime
            if (root.visible) {
                root.selectedTimeChanged(hour,minute)
            }
        }

        Component.onCompleted: {

            var i=0;
            for (i=0; i<=23; i++) {
                hourModel.append({"name": padDigits(i, 2), "value": i});
            }

            for (i=0; i<=59; i++) {
                minuteModel.append({"name": padDigits(i, 2), "value": i});
            }

            hourPicker.currentIndex = hour//Qt.formatTime(new Date(),"hh")
            minutePicker.currentIndex = minute//Qt.formatTime(new Date(),"mm")

//            internal.hour = 8//Qt.formatTime(new Date(),"hh")
//            internal.minute = 0//Qt.formatTime(new Date(),"mm")
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Row {
        anchors.fill: parent

        DataPicker {
            id: hourPicker
            height: parent.height
            width: parent.width / 2
            model: internal.hourModel

            Text {
                text: qsTr("H")
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: Unit.dp(50)
                }
            }

            onSelectedIndexChanged: {
                //console.info("hour changed")
                var item = internal.hourModel.get(selectedIndex)
                internal.hour = item["value"]
                internal.update()
            }
        }

        Rectangle {
            height: parent.height
            width: Unit.dp(1)
            color: "#FFFFFF"
        }

        DataPicker {
            id: minutePicker
            height: parent.height
            width: parent.width / 2
            model: internal.minuteModel

            Text {
                text: qsTr("M")
                anchors {
                    verticalCenter: parent.verticalCenter
                    right: parent.right
                    rightMargin: Unit.dp(50)
                }
            }

            onSelectedIndexChanged: {
                var item = internal.minuteModel.get(selectedIndex)
                internal.minute = item["value"]
                internal.update()
            }
        }
    }

    Component.onCompleted: {
//        var currentTime = new Date()
//        setDate(currentDate)
    }

    function setDate(currentDate) {
//        hourPicker.currentIndex = 8//Qt.formatTime(new Date(),"hh")
//        minutePicker.currentIndex = 0//Qt.formatTime(new Date(),"mm")
    }
}
