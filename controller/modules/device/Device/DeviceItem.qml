import QtQuick 2.0
import QmlControls 0.1
import QmlItem 0.1 as QmlItem

Item {
    width: parent.width
    height: Unit.dp(100)
    signal clickedDeviceItem(int index)
    FontImage {
        id: icon
        width: Unit.dp(70)
        height: Unit.dp(70)
        anchors {
            left: parent.left
            leftMargin: Unit.dp(10)
            verticalCenter: parent.verticalCenter
        }
        source: deviceIcon
        color: deviceValue == "true"?"#4B3621":"#4B3621"
        iconSize: 70
    }
    Column {
        anchors {
            left: icon.right
            leftMargin: Unit.dp(10)
            right: parent.right
            rightMargin: Unit.dp(20)
            verticalCenter: parent.verticalCenter
        }
        spacing: Unit.dp(5)
        QmlItem.TextWithTitle {
            title: "Device Name"
            text: deviceName
        }
        QmlItem.TextWithTitle {
            title: "Section"
            text: deviceSection
        }
        QmlItem.TextWithTitle {
            title: "Device Info"
            text: deviceName
        }
    }
    FontImage {
        width: Unit.dp(20)
        height: parent.height
        anchors {
            right: parent.right
            verticalCenter: parent.verticalCenter
        }
        source: "arrow-right"
        iconSize: 30
        color: "black"
    }
    MouseArea {
        anchors.fill: parent
        onClicked: {
            clickedDeviceItem(index)
        }
    }

    QmlItem.Line {
        anchors.bottom: parent.bottom
    }
}

