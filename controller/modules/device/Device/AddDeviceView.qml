import QtQuick 2.0
import QtQuick.Controls 1.1
import QmlControls 0.1
import QmlItem 0.1 as QmlItem

Item {
    property var navigationItem : NavigationItem {
                   title : "Add Device"
                   rightBarButtonItem: Button {
                       width: Unit.dp(40)
                       iconName: "card"
                       iconColor: CSS.colorGreenSea
                       onClicked: {
                           deviceListController.addDevice(deviceName.text,
                                                          icon.iconName,
                                                          valueTF.text,
                                                          sectionTF.text)
                           navigation.pop()
                       }
                   }
               }
    Column {
        width: parent.width
        anchors {
            top: parent.top
            topMargin: Unit.dp(10)
        }
        spacing: Unit.dp(10)
        TextField {
            id: deviceName
            width: parent.width
            height: Unit.dp(44)
            style: TextFieldStyle {}
            placeholderText: "Device Name"
        }
        Button {
            id: icon
            width: Unit.dp(100)
            height: Unit.dp(100)
            anchors {
                horizontalCenter: parent.horizontalCenter
            }
            iconSize: 80
            iconName: "lamp"
            iconColor: CSS.colorPeterRiver
            onClicked: {
                selectIconPopup.visible = !selectIconPopup.visible
            }
        }
        TextField {
            id: valueTF
            width: parent.width
            height: Unit.dp(44)
            style: TextFieldStyle {}
            placeholderText: "Value"
        }
        TextField {
            id: sectionTF
            width: parent.width
            height: Unit.dp(44)
            style: TextFieldStyle {}
            placeholderText: "Section"
        }
        TextField {
            width: parent.width
            height: Unit.dp(44)
            style: TextFieldStyle {}
            placeholderText: "Parameter 3"
        }
    }
    SelectIconPopup {
        id: selectIconPopup
        z: 1
        visible: false
        onIconClicked: {
            icon.iconName = iconName
        }
    }
}

