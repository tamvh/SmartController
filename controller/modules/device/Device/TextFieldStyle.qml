import QtQuick 2.0
import QtQuick.Controls.Styles 1.1
import QtGraphicalEffects 1.0
import QmlControls 0.1

TextFieldStyle {
    textColor: "black"
    placeholderTextColor: CSS.colorAsbestos
    padding.left: Unit.dp(10)
    background: Rectangle {
        implicitWidth: Unit.dp(100)
        implicitHeight: Unit.dp(24)
        color: "white"
    }
}

