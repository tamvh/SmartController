import QtQuick 2.0
import QtQuick.Controls 1.1
import QmlControls 0.1
import QmlItem 0.1 as QmlItem

Item {
    property alias deviceName : nameTF.text
    property alias deviceIcon : icon.iconName
    property alias deviceValue : valueTF.text
    property alias deviceSection : sectionTF.text
    property real deviceId
    property var navigationItem : NavigationItem {
                   title : "Edit Device"
                   rightBarButtonItem: Button {
                       width: Unit.dp(40)
                       iconName: "three115"
                       iconColor: CSS.colorGreenSea
                       onClicked: {
                           navigation.pop()
                           deviceDetail.deviceIcon_ = deviceIcon
                           deviceDetail.deviceName_ = deviceName
                           deviceDetail.deviceSection_ = deviceSection
                           deviceDetail.deviceValue_ = deviceValue
                           deviceListController.editDevice(deviceId,
                                                           deviceName,
                                                           deviceIcon,
                                                           deviceValue,
                                                           deviceSection)
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
            id: nameTF
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
            iconName: "three115"
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

