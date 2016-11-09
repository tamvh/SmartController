import QtQuick 2.0

Rectangle {
    id: rootButton
    radius: 2
    color: "transparent"
    signal clicked
    property alias pressed: mouseArea.pressed
    opacity: mouseArea.pressed ? 0.2 : 1
    Behavior on opacity {
        NumberAnimation {
            duration: 100
            easing.type: Easing.InOutQuad
        }
    }
    MouseArea {
        id: mouseArea
        onClicked: rootButton.clicked()
        anchors.fill: parent
    }
}
