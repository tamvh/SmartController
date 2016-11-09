import QtQuick 2.1
import QmlControls 0.1

Item {
    id: rootListMore

    signal clickedBackground

    property point visiblePoint: Qt.point(0, 0)
    property point invisiblePoint: Qt.point(0, 1000)
    property alias menuPanel: menuPanel
    property real animationDuration: 200

    anchors.fill: parent

    function show() {
        rootListMore.state = "VISIBLE"
    }

    function hide() {
        rootListMore.state = "INVISIBLE"
    }

    Rectangle {
        id: background
        anchors.fill: parent
        color: "black"
        opacity: 0
        visible: false

        MouseArea {
            id: mouseArea
            anchors.fill: parent
            onClicked: {
                rootListMore.clickedBackground()
            }
        }

        Behavior on opacity {
            NumberAnimation {
                duration: animationDuration
            }
        }
    }

    Rectangle {
        id: menuPanel
        y: invisiblePoint.y
        x: invisiblePoint.x
        width: parent.width
        color: CSS.colorWetAsphalt
        Behavior on y {
            NumberAnimation {
                id: animationY
                duration: animationDuration
            }
        }
    }

    state: "INVISIBLE"

    states: [
        State {
            name: "VISIBLE"
            PropertyChanges {
                target: menuPanel
                y: visiblePoint.y
                x: visiblePoint.x
            }

            PropertyChanges {
                target: background
                visible: true
                opacity: 0.2
            }

            PropertyChanges {
                target: mouseArea
                visible: true
            }
        },
        State {
            name: "INVISIBLE"
            PropertyChanges {
                target: menuPanel
                y: invisiblePoint.y
                x: invisiblePoint.x
            }

            PropertyChanges {
                target: background
                visible: true
                opacity: 0
            }

            PropertyChanges {
                target: mouseArea
                visible: false
            }
        }
    ]
}
