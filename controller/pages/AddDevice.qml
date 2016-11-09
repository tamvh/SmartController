import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.1
import Qt.labs.settings 1.0
import QtGraphicalEffects 1.0
import SmartControls 1.0

Page {
    id: pageAddDevice
    title: "Add Device"    
    property var _groupname: ""
    property var _deviceType: 0
    property var _listGroup: []
    property var _deviceAddress: ""
    property var _deviceName: ""
    property var _page: ""
    Settings {
        id: settings
        property string style: "Universal"
    }

    GroupController
    {
        id: groupController
    }

    DeviceController
    {
        id: deviceController
    }

    background: Rectangle {
        implicitWidth: Screen.width
        implicitHeight: Screen.height
        color: "#F5F5F5"
    }
    header:ToolBar {
        background: Rectangle {
            implicitWidth: 100
            implicitHeight: 25
            color: "#EF6C00"
        }
        RowLayout {
            spacing: 20
            anchors.fill: parent


            ToolButton {
                Image {
                    id: backDraw
                    height: 16
                    width: 16
                    source: "qrc:/images/navigation_previous_item.png"
                    anchors.centerIn: parent
                }
                onClicked: {
                    stackView.pop();
                }
            }

            Label {
                id: titleLabel
                text: title
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            ToolButton {

            }
        }
    }

    Button {
        id: btnAddDevice
        anchors {
            left: parent.left
            leftMargin: 0
            right: parent.right
            rightMargin: 0
            bottom: parent.bottom
            bottomMargin: 0
        }

        background: Rectangle {
            id: bgRectButton
            implicitWidth: Screen.width
            implicitHeight: 50
            color: "#EFEBE9"
        }

        onClicked: {            
            console.log("btnAddDevice onClicked Turn on")
            if(txtDeviceAddress.text.trim() === "") {
                txtWarning.text = "(*)Warning: address is NULL"
                txtWarning.visible = true
                return
            }
            if(txtDeviceName.text.trim() === "") {
                txtWarning.text = "(*)Warning: device name is NULL"
                txtWarning.visible= true
                return
            }
            if(deviceController.checkDeviceExisted(txtDeviceAddress.text.trim()) === true) {
                txtWarning.text = "(*)Warning: device is EXISTED"
                txtWarning.visible= true
                return
            }

            deviceController.addDevice(txtDeviceAddress.text.trim(),
                                       txtDeviceName.text.trim(),
                                       _groupname,
                                       _deviceType);
            stackView.pop();
        }

        Image {
            id: buttonicon
            width: 20
            height: 20
            anchors {
                right: buttonTitle.left
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/images/add.png"

        }

        Text {
            id: buttonTitle
            text: "Add device"
            font.family: "Helvetica"
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: "gray"
        }
    }

    Text {
        id: txtWarning
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottom: btnAddDevice.top
        anchors.bottomMargin: 10
        text: qsTr("text")
        visible: false
        color: "#EF6C00"
    }

    Column {
        anchors.fill: parent
        Label {
            id: lblAlarm
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            anchors {
                top: comboDeviceType.bottom
                topMargin: 20
            }
            visible: false
            text: "(*) This device existed!, re-enter other device name"
            color: "red"
        }

        TextField {
            id: txtDeviceAddress
            text: _deviceAddress
            height: 50
            width: Screen.width
            placeholderText: "<i>Device Address</i>"
            anchors {
                top: parent.top
                topMargin: 20
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
                horizontalCenter: parent.horizontalCenter
            }

            background: Rectangle {
                radius: 50
                implicitWidth: Screen.width
                implicitHeight: 60
                border.color: "#ECEFF1"
                border.width: 1
            }
            Image {
                width: 20
                height: 20
                source: "qrc:/images/ic_edit.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
            onTextChanged: {

            }

            Component.onCompleted: {
                if(_page === "ScanDevice") {
                    txtDeviceAddress.enabled = false
                }
            }
        }

        TextField {
            id: txtDeviceName
            text: _deviceName
            height: 50
            width: Screen.width
            placeholderText: "<i>Device Name</i>"
            anchors {
                top: txtDeviceAddress.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                radius: 50
                implicitWidth: Screen.width
                implicitHeight: 60
                border.color: "#ECEFF1"
                border.width: 1
            }
            Image {
                width: 20
                height: 20
                source: "qrc:/images/ic_edit.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
            onTextChanged: {

            }
        }        

        ComboBox {
            id: comboGroupName
            property int styleIndex: -1
            textRole: "groupName"
            model: groupController.listGroup
            anchors {
                top: txtDeviceName.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                radius: 50
                implicitWidth: Screen.width
                implicitHeight: 50
                border.color: "#ECEFF1"
                border.width: 1
            }           

            Layout.fillWidth: true
            onCurrentIndexChanged: {
               _groupname = textAt(currentIndex);
                console.log("_groupname: " + _groupname);
            }
        }

        ComboBox {
            id: comboDeviceType
            property int styleIndex: -1
            model: ["[1] - Ốp trần cao cấp 1", "[2] - Ốp trần cao cấp 2"]
            anchors {
                top: comboGroupName.bottom
                topMargin: 10
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                radius: 50
                implicitWidth: Screen.width
                implicitHeight: 50
                border.color: "#ECEFF1"
                border.width: 1
            }
            onCurrentIndexChanged: {
               _deviceType = currentIndex + 1;
                console.log("_deviceType: " + _deviceType);
            }

            Layout.fillWidth: true
        }       
    }    
}
