import QtQuick 2.0
import QmlControls 0.1

Item {
    width: parent.width
    height: Unit.dp(30)

    property int titleFontSize: Unit.sp(16)
    property int textFontSize: Unit.sp(14)

    property string fontFamily: "Helvetica"
    property string title: "title"
    property string text : "text"
    property color valueColor: "#485C68"
    property color titleColor: "#485C68"

    Text {
        text: title
        anchors {
            left: parent.left
            leftMargin: Unit.dp(10)
            verticalCenter: parent.verticalCenter
        }
        font { pixelSize: titleFontSize; family: fontFamily }
        font.bold: true
        color: titleColor
    }

    Text {
        text: parent.text
        anchors {
            right: parent.right
            rightMargin: Unit.dp(10)
            verticalCenter: parent.verticalCenter
        }
        font { pixelSize: textFontSize; family: fontFamily }
        color: valueColor
    }
}

