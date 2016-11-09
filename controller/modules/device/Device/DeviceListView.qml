import QtQuick 2.0
import QmlControls 0.1
import Device 0.1

Item {
    property var navigationItem : NavigationItem {
        title : "Device List"
        rightBarButtonItem: Button {
            width: Unit.dp(40)
            iconName: "three115"
            iconColor: CSS.colorGreenSea
            onClicked: {
                navigation.push(adddeviceview_component)
            }
        }
    }
    DeviceListController {
        id: deviceListController
    }
    ListView {
        anchors.fill: parent
        model: deviceListController.deviceModel
        delegate: DeviceItem {
            onClickedDeviceItem: {
                navigation.push(devicedetailview_component,
                                {
                                    deviceId_: deviceId,
                                    deviceName_: deviceName,
                                    deviceIcon_: deviceIcon,
                                    deviceValue_: deviceValue,
                                    deviceSection_: deviceSection
                                })
            }
        }
        clip: true
        section.property: "deviceSection"
        section.criteria: ViewSection.FullString
        section.delegate: sectionHeadingDelegate
        section.labelPositioning: ViewSection.CurrentLabelAtStart | ViewSection.InlineLabels
    }

    Component {
        id: devicedetailview_component
        DeviceDetailView { }
    }

    Component {
        id: adddeviceview_component
        AddDeviceView { }
    }

    Component {
        id: sectionHeadingDelegate
        Rectangle {
            id: body
            width: parent.width
            height: Unit.dp(30)
            color: CSS.colorConcrete
            Text {
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                anchors.leftMargin: Unit.dp(16)
                text: section
                font.bold: true
                font.pixelSize: Unit.sp(16)
                color: CSS.colorWisteria
            }
        }
    }
}

