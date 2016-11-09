import QtQuick 2.0
import QmlControls 0.1

Item {
    id: selectIconPopup
    signal iconClicked(string iconName)
    anchors.fill: parent
    Rectangle {
        anchors.fill: parent
        color: "black"
        opacity: 0.3
    }
    Rectangle {
        width: parent.width - Unit.dp(40)
        height: Math.ceil(iconList.count /3) * gridView.cellHeight + Unit.dp(40)
        anchors {
            verticalCenter: parent.verticalCenter
            horizontalCenter: parent.horizontalCenter
        }
        color: CSS.colorClouds
        radius: Unit.dp(10)
        GridView {
            id: gridView
            anchors {
                margins: Unit.dp(20)
                top: parent.top
                bottom: parent.bottom
                left: parent.left
                right: parent.right
            }
            model: iconList
            delegate: Item {
                width: gridView.cellWidth
                height: gridView.cellHeight
                Button {
                    color: CSS.colorCarrot
                    width: gridView.cellHeight - Unit.dp(4)
                    height: width
                    iconName: deviceIcon
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    onClicked: {
                        iconClicked(deviceIcon)
                        selectIconPopup.visible = false
                    }
                    iconSize: 40
                }
            }
            cellHeight: gridView.width/ 3
            cellWidth: gridView.width/ 3

        }
    }
    ListModel {
        id: iconList
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
        ListElement {
            deviceIcon: "coffee-machine"
        }
    }
}

