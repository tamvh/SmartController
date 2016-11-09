import QtQuick 2.0
import QmlControls 0.1
import Device 0.1
import QmlItem 0.1 as QmlItem

Item {
    id: deviceDetail
    property var navigationItem : NavigationItem {
        title : "Device Detail"
        rightBarButtonItem: Row {
            width: Unit.dp(80)
            height: Unit.dp(44)
            Button {
                anchors.verticalCenter: parent.verticalCenter
                width: Unit.dp(40)
                iconName: "three115"
                iconColor: CSS.colorGreenSea
                onClicked: {
                    navigation.push(editdeivceview_component,{
                                        deviceId: deviceDetail.deviceId_,
                                        deviceName: deviceDetail.deviceName_,
                                        deviceValue: deviceDetail.deviceValue_,
                                        deviceIcon: deviceDetail.deviceIcon_,
                                        deviceSection: deviceDetail.deviceSection_
                                    })
                }
            }

            Button {
                anchors.verticalCenter: parent.verticalCenter
                width: Unit.dp(40)
                iconName: "three115"
                iconColor: CSS.colorGreenSea
                onClicked: {
                    deviceListController.removeDeviceWithId(deviceId_)
                    navigation.pop()
                }
            }
        }
    }
    property string deviceIcon_
    property string deviceValue_
    property string deviceName_
    property real deviceId_
    property string deviceSection_

    Column {
        width: parent.width - Unit.dp(10)
        anchors {
            top: parent.top
            topMargin: Unit.dp(20)
            horizontalCenter: parent.horizontalCenter
        }
        spacing: Unit.dp(10)
        FontImage {
            id: icon
            width: Unit.dp(70)
            height: Unit.dp(70)
            anchors {
                horizontalCenter: parent.horizontalCenter
            }

            source: deviceDetail.deviceIcon_
            color: deviceDetail.deviceValue_ == "true"?"green":"red"
            iconSize: 70
        }

        QmlItem.TextWithTitle {
            title: "Device Name"
            text: deviceDetail.deviceName_
        }

        QmlItem.TextWithTitle {
            title: "Device Value"
            text: deviceDetail.deviceValue_
        }

        QmlItem.TextWithTitle {
            title: "Section"
            text: deviceDetail.deviceSection_
        }
    }

    Component {
        id: editdeivceview_component
        EditDeviceView { }
    }
}
