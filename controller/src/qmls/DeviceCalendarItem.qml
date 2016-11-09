import QtQuick 2.0
import QmlControls 0.1
import QmlItem 0.1 as QmlItem
import Material 0.2 as Material

// Hiển thị 1 mục hẹn giờ của thiết bị
Item {
    width: parent.width
    height: Unit.dp(80)
    signal deleteButtonClicked(int row, int calendarId);
    signal editButtonClicked(int row, int calendarId);

    Rectangle {
        anchors {
            bottom: parent.bottom
            left: parent.left
            right: parent.right
        }
        height: Unit.dp(1)
        color: CSS.colorMidnightBlue
    }
    Text {
        height: Unit.dp(30)
        text: statusText
        font.family: "Times New Roman"
        font.bold: true
        font.pointSize: 18
        color: CSS.colorMidnightBlue
        anchors {
            top: parent.top
            topMargin: Unit.dp(10)
            left: parent.left
            leftMargin: Unit.dp(10)
        }
    }
    Text {
        height: Unit.dp(30)
        text: repeartText
        font.family: "Times New Roman"
        verticalAlignment: Text.AlignBottom
        font.pointSize: 16
        color: CSS.colorConcrete
        anchors {
            bottom:  parent.bottom
            bottomMargin: Unit.dp(10)
            left: parent.left
            leftMargin: Unit.dp(10)
        }
    }

    Text {
        height: Unit.dp(30)
        text: timeText
        color: CSS.colorMidnightBlue
        font.family: "Times New Roman"
        font.pointSize: 16
        anchors {
            top: parent.top
            topMargin: Unit.dp(10)
            right: parent.right
            rightMargin: Unit.dp(10)
        }
    }

    Row {
        anchors {
            bottom: parent.bottom
            bottomMargin: Unit.dp(10)
            right: parent.right
            rightMargin: Unit.dp(10)
        }
        height: Unit.dp(35)
        layoutDirection: Qt.RightToLeft
        spacing: Unit.dp(10)
        Material.Button {
            width: Unit.dp(60)
            height: parent.height
            elevation: 1
            backgroundColor: "white"
            text: "Sửa"
            onClicked:  {
                editButtonClicked(index, calendarId)
            }
        }
        Material.Button {
            width: Unit.dp(60)
            height: parent.height
            elevation: 1
            backgroundColor: "red"
            text: "Xóa"
            onClicked: {
                deleteButtonClicked(index, calendarId)
            }
        }
    }
}

