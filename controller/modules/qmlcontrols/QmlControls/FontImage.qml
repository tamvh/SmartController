import QtQuick 2.0
import QmlControls 0.1
import "res.js" as Constants

Item {
    property string source
    property real iconSize: 26
    property alias color: uiText.color

    Text {
        id: uiText
        text: Constants.lookupIconName(source)
        color: "white"
        font.family: Constants.UIIconSet
        font.pixelSize: Unit.sp(iconSize)
        anchors.centerIn: parent
    }
}
