import QtQuick 2.0

Rectangle {
    id: rootObject

    property variant radiusAngular

    onRadiusAngularChanged: {
        //console.info("onRadiusAngularChanged",radiusAngular)
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
}
