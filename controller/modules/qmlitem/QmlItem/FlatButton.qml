import QtQuick 2.0
import QmlControls 0.1

Rectangle {
    id: rootObject
    property color backgroundColor: CSS.buttonDefaultBackgroundColor
    property color pressedBackgroundColor: CSS.buttonDefaultPressedBackgroundColor
    property color disableBackgroundColor: CSS.buttonDefaultDisableBackgroundColor
    property color textColor: CSS.buttonDefaultTextColor
    property string text
    property alias title: title
    property alias textSize: title.font.pointSize
    property bool lowLight: false

    signal clicked();

    color: enabled ? backgroundColor : disableBackgroundColor
    property variant radiusAngular

    onRadiusAngularChanged: {
        console.info("onRadiusAngularChanged",radiusAngular)
        var isTR = true
        var isTL = true
        var isBR = true
        var isBL = true
        for (var i = 0; i < radiusAngular.length; i++) {
            if (radiusAngular[i] === "TR"){
                isTR = false
            }
            if (radiusAngular[i] === "TL"){
                isTL = false
            }
            if (radiusAngular[i] === "BR"){
                isBR = false
            }
            if (radiusAngular[i] === "BL"){
                isBL = false
            }
        }

        topRight.visible = isTR
        topLeft.visible = isTL
        bottomRight.visible = isBR
        bottomLeft.visible = isBL
    }

    Rectangle {
        id:topRight
        width: rootObject.radius
        height: rootObject.radius
        anchors.top: parent.top
        anchors.right: parent.right
        color: rootObject.color
        visible: false
    }

    Rectangle {
        id:topLeft
        width: rootObject.radius
        height: rootObject.radius
        anchors.top: parent.top
        anchors.left: parent.left
        color: rootObject.color
        visible: false
    }

    Rectangle {
        id:bottomRight
        width: rootObject.radius
        height: rootObject.radius
        anchors.bottom: parent.bottom
        anchors.right: parent.right
        color: rootObject.color
        visible: false
    }

    Rectangle {
        id:bottomLeft
        width: rootObject.radius
        height: rootObject.radius
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        color: rootObject.color
        visible: false
    }

    Text {
        id:title
        text: rootObject.text
        color: textColor
        anchors.centerIn: parent
        font { family: "Helvetica"; pixelSize: Unit.sp(16); }
    }

    MouseArea {
        id: mouseArea
        anchors.fill: parent
        onClicked: rootObject.clicked()
    }

    Rectangle {
        id:black
        anchors.fill: parent
        color: "black"
        opacity: 0.1
        visible: false
    }

    states: [

        State {
            name: "PRESSED"
            when: mouseArea.pressed

            PropertyChanges {
                target: rootObject
                color: {
                    if (!lowLight)
                        return pressedBackgroundColor
                    else
                        return backgroundColor
                }
            }

            PropertyChanges {
                target: black
                visible: {
                    if (lowLight) {
                        return true
                    } else {
                        return false
                    }
                }
            }

            PropertyChanges {
                target: topRight
                color: pressedBackgroundColor
            }

            PropertyChanges {
                target: topLeft
                color: pressedBackgroundColor
            }

            PropertyChanges {
                target: bottomRight
                color: pressedBackgroundColor
            }

            PropertyChanges {
                target: bottomLeft
                color: pressedBackgroundColor
            }
        }
    ]
}
