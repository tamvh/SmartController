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

    Also component emit signal selectedDateChanged(date selectedDate) when selected date is change
*/

Item {
    id: root
    width: parent.width
    height: Unit.dp(200)

    property DatePickerStyle platformStyle: DatePickerStyle {}

    signal selectedDateChanged(int day, int month, int year);


    QtObject {
        id: internal
        property int day
        property int month
        property int year

        property ListModel dayModel: ListModel {}
        property ListModel monthModel: ListModel {}
        property ListModel yearModel: ListModel {}

        function padDigits(number, digits) {
            return new Array(Math.max(digits - String(number).length + 1, 0)).join(0) + number;
        }

        property date selectedDate
        function update() {
            var newDate = new Date(year, month, day)
            selectedDate = newDate
            if (root.visible) {
                root.selectedDateChanged(day,month,year)
            }
        }

        Component.onCompleted: {

            var i=0;
            for (i=1; i<=31; i++) {
                dayModel.append({"name": padDigits(i, 2), "value": i});
            }

            var MonthNames = new Array(12);
            for (i=1; i<=12; i++) {
                monthModel.append({"name": "Tháng " + (i), "value": i});
            }

            var year = new Date();
            for (i=year.getFullYear()-100; i<=year.getFullYear(); i++) {
                yearModel.append({"name": padDigits(i, 4), "value": i});
            }

            yearPicker.currentIndex = 101 - 10
            monthPicker.currentIndex = 0
            dayPicker.currentIndex = 0

            internal.day = 1
            internal.month = 1
        }
    }

    Rectangle {
        anchors.fill: parent
        color: "white"
    }

    Row {
        anchors.fill: parent

        DataPicker {
            id: dayPicker
            height: parent.height
            width: parent.width / 4
            model: internal.dayModel

            onSelectedIndexChanged: {
                //console.info("day changed")
                var item = internal.dayModel.get(selectedIndex)
                internal.day = item["value"]
                internal.update()
            }
        }

        DataPicker {
            id: monthPicker
            height: parent.height
            width: parent.width / 2
            model: internal.monthModel
            onSelectedIndexChanged: {
                var item = internal.monthModel.get(selectedIndex)
                internal.month = item["value"]
                internal.update()
            }
        }

        DataPicker {
            id: yearPicker
            height: parent.height
            width: parent.width / 4
            model: internal.yearModel
            onSelectedIndexChanged: {
                var item = internal.yearModel.get(selectedIndex)
                internal.year = item["value"]
                internal.update()
            }
        }
    }

    Component.onCompleted: {
        var currentDate = new Date()
        setDate(currentDate)
    }

    function setDate(currentDate) {
//        dateModel.changeModel(currentDate)
//        daysGrid.currentIndex = dateModel.firstDayOffset + currentDate.getDate() - 1
    }
}
