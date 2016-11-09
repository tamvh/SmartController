import QtQuick 2.0
import QmlControls 0.1

Rectangle {
    id: toast
//    anchors.centerIn: parent
    width: parent.width - Unit.dp(30)//Unit.dp(200)
    height: textShow.height + Unit.dp(30)
    color: "#A0000000"
    property alias text: textShow.text

    state: "INVISIBLE"

    Text {
        id: textShow
        width: parent.width
        color: "white"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter
        font.pixelSize: Unit.sp(18)
        anchors.centerIn: parent
        wrapMode: Text.Wrap
    }

    Timer {
        id: toastTimer;
        interval: 3000
        onTriggered: toast.hideToast()
    }

    function showToast(text) {
        toast.text = text
        toast.state = "VISIBLE"
        toastTimer.start()
    }

    function hideToast() {
        toast.state = "INVISIBLE"
    }

    states: [
        State {
            name: "VISIBLE"
            PropertyChanges {
                target: toast
                opacity: 1
            }
        },
        State {
            name: "INVISIBLE"
            PropertyChanges {
                target: toast
                opacity: 0
            }
        }
    ]
    transitions: [
        Transition {
            from: "VISIBLE"
            to: "INVISIBLE"

            NumberAnimation {
                target: toast
                property: "opacity"
                duration: 400
                easing.type: Easing.InOutQuad
            }
        }
    ]
}
