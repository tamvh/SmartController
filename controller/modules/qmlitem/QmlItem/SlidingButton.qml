import QtQuick 2.0
import QmlControls 0.1

Rectangle {
    id: loginButton

    signal clicked()

    property point visiblePoint: {
        console.info("Qt.inputMethod.keyboardRectangle.y:",Qt.inputMethod.keyboardRectangle.y)
        var yKeyboard = Qt.inputMethod.keyboardRectangle.y
        if (yKeyboard === 0) {
            yKeyboard = loginButton.parent.height
        }
        var point = loginButton.parent.mapFromItem(null, 0, yKeyboard - loginButton.height)
        console.info("yKeyboard - loginButton.height:",loginButton.parent.height - (yKeyboard - loginButton.height))
        console.info("point.y:", point.y)
        return Qt.point(0, point.y)
    }

    property point invisiblePoint: {
        var yKeyboard = Qt.inputMethod.keyboardRectangle.y
        if (yKeyboard === 0) {
            yKeyboard = loginButton.parent.height
        }
        var point = loginButton.parent.mapFromItem(null, -width, yKeyboard - loginButton.height)
        return Qt.point(-width, point.y)
    }

    property real animationDuration: 200
    property alias text: flatButton.text
    property alias textColor: flatButton.textColor

    function show() {
        loginButton.state = "VISIBLE"
    }

    function hide() {
        loginButton.state = "INVISIBLE"
    }

    y: invisiblePoint.y
    x: invisiblePoint.x

    FlatButton {
        id:flatButton
        anchors.fill: parent
        text: ""
        textColor: CSS.loginTextColor
        onClicked: {
            loginButton.clicked()
        }
    }

    Behavior on y {
        NumberAnimation {
            duration: animationDuration
        }
    }
    Behavior on x {
        NumberAnimation {
            duration: animationDuration
            onRunningChanged: {
                if (!running && loginButton.state == 'INVISIBLE') {
                    loginButton.visible = false
                } else if (parent.height > 0) {
                    loginButton.visible = true
                } else {
                    loginButton.visible = false
                }

            }
        }
    }

    state: "INVISIBLE"

    states: [

        State {
            name: "VISIBLE"
            PropertyChanges {
                target: loginButton
                y: visiblePoint.y
                x: visiblePoint.x
            }
        },

        State {
            name: "INVISIBLE"
            PropertyChanges {
                target: loginButton
                y: invisiblePoint.y
                x: invisiblePoint.x
            }
        }
    ]
}
