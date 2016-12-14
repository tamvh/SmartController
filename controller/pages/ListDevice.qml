import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQuick.Dialogs 1.2
import QtQml.Models 2.1
import Qt.labs.settings 1.0
import SmartControls 1.0
import QtGraphicalEffects 1.0
import "Common.js" as Global


Page {
    id: pageListDevice
    title: "List Device"
    property var _groupname: ""
    property var _devicename: ""
    property var _deviceType: 0
    property var _deviceaddress: ""
    property var _deviceid: 0
    property var _listGroup: []
    property var _display: 0 //list
    property var _currentIndex: 0
    property var _totalDevice: 0
    property var _command: 2 //command join
    property var _value: 0
    Settings {
        id: settings
        property string style: "Universal"
    }
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 25
        color: "#ECEFF1"
    }

    DeviceController {
        id: deviceController
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
                    stackView.replace("qrc:/pages/Dashboard.qml", StackView.PushTransition);
                }
            }

            Label {
                id: titleLabel
                text: Global.g_groupName
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            ToolButton {
                Image {
                    id: imgDisplay
                    anchors.centerIn: parent
                    width: 16
                    height: 16
                    source: "qrc:/images/list.png"
                }
                ColorOverlay {
                    anchors.fill: imgDisplay
                    source: imgDisplay
                    color: "white"
                }
                onClicked: {
                    console.log("change display type: " + imgDisplay.source);
                    if(_display === 0) {
                        _display = 1;
                        imgDisplay.source = "qrc:/images/grid.png";
                        gridDevice.visible = true;
                        listDevice.visible = false;
                    }
                    else
                    {
                        _display = 0;
                        imgDisplay.source = "qrc:/images/list.png";
                        gridDevice.visible = false;
                        listDevice.visible = true;
                    }

                }
            }
        }
    }

    Rectangle {
        id: rectAddGroup
        z:1
        anchors {
            right: parent.right
            rightMargin: 5
            bottom: parent.bottom
            bottomMargin: 5
        }
        height: 60
        width: 60
        radius: 60
        border.color: "#EEEEEE"
        border.width: 1

        Image {
            id: buttonicon
            width: 20
            height: 20
            anchors {
                centerIn: parent
                rightMargin: 10
            }
            source: "qrc:/images/add.png"
        }
        ColorOverlay {
            anchors.fill: buttonicon
            source: buttonicon
            color: "#EEEEEE"
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                rectAddGroup.color = "white";
                console.log("open popup add device");
                popupAddDevice.open();
            }
            onPressed: {
                rectAddGroup.color = "#EEEEEE";
            }
        }
    }

    GridView {
        id: gridDevice
        width: Screen.width;
        height: parent.height
        cellWidth: Screen.width/3; cellHeight: Screen.width/3
        clip: true
        displaced: Transition {
            NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
        }
        model: DelegateModel {
            id: visualModel
            model: deviceController.listDevice(_groupname)
            delegate: MouseArea {
                id: delegateRoot

                property int visualIndex: DelegateModel.itemsIndex

                width: Screen.width/3; height: Screen.width/3
                drag.target: icon

                Rectangle {
                    id: icon
                    width: Screen.width/3; height: Screen.width/3
                    anchors {
                        left: parent.left
                        leftMargin: 1
                        top: parent.top
                        topMargin: 1
                        horizontalCenter: parent.horizontalCenter;
                        verticalCenter: parent.verticalCenter
                    }
                    border.color: "#EEEEEE"
                    border.width: 0.5
                    color: "#FFF"

                    RowLayout {
                        anchors {
                            horizontalCenter: parent.horizontalCenter
                            verticalCenter: parent.verticalCenter
                        }
                        Image {
                            id: imgDeviceinGrid
                            width: 64
                            height: 64
                            source: deviceAvatar;
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                        Text {
                            id: txtDeiviceName
                            text: deviceName;
                            font.pixelSize: 12
                            color: "#9E9E9E"
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.top: imgDeviceinGrid.bottom
                        }


                    }
                    Component.onCompleted: {
                        if(txtDeiviceName.text.length > 10)
                            txtDeiviceName.text = txtDeiviceName.text.substring(0, 10) + "..."

                        if(_display === 0) {
                            gridDevice.visible = false
                            listDevice.visible = true
                        }
                        _totalDevice += 1
                        console.log(_totalDevice + "");
                    }

                }

                MouseArea {
                   anchors.fill: parent

                   onClicked: {
                       icon.color = "#CFD8DC";
                       Global.g_deviceName = deviceName;
                       Global.g_deviceId = deviceId;
                       console.log("Global.g_deviceName: " + Global.g_deviceName);
                       console.log("Deivce Type: " + deviceType);
                       if(deviceType === 1) {
                            stackView.push("qrc:/pages/DeviceDetailType1.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else if(deviceType === 2){
                            stackView.push("qrc:/pages/DeviceDetailType2.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else if(deviceType === 3){
                            stackView.push("qrc:/pages/DeviceDetailType3.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else if(deviceType === 4){
                            stackView.push("qrc:/pages/DeviceDetailType4.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else if(deviceType === 5){
                            stackView.push("qrc:/pages/DeviceDetailType5.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else if(deviceType === 6){
                            stackView.push("qrc:/pages/DeviceDetailType6.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }
                       else {
                            stackView.push("qrc:/pages/DeviceDetailType.qml", {_deviceId: deviceId, _deviceaddress: deviceAddress, _deviceName: deviceName, _groupname: _groupname})
                       }

                   }
                   onPressAndHold: {
                       icon.color = "white"
                       console.log("onPressAndHold Turn on: " + deviceName);
                       _devicename = deviceName;
                       _deviceaddress = deviceAddress;
                       _deviceid = deviceId;
                       popupDeleteDevice.open();
                   }
                }
            }
        }
    }

    ListView {
        id: listDevice
        currentIndex: -1
        anchors.fill: parent
        delegate: ItemDelegate {
            width: Screen.width
            height: 100
            background: Rectangle {
                color: "white"
            }
            anchors {
                left: parent.left
                leftMargin: 5
                right: parent.right
                rightMargin: 5
            }
            RowLayout {
                id: layout
                anchors.fill: parent                
                Image {
                    anchors {
                        left: parent.left
                        leftMargin: 20
                    }
                    id: imgSource
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    height: 64
                    width: 64
                    source: deviceAvatar
                }


                Rectangle {
                    id: rectLine
                    anchors {
                        left: imgSource.right
                        leftMargin: 10
                    }
                    color: "#EEEEEE"
                    height: 70
                    width: 1
                }

                GridLayout {
                    anchors {
                        left: rectLine.right
                        leftMargin: 10
                    }
                    id: gridEvent
                    columns: 1
                    Column {
                        anchors {
                            fill: parent
                            leftMargin: 0
                        }
                        Label {
                            anchors {
                                bottomMargin: 7
                            }
                            text: deviceName
                            color: "#757575"
                            font.pixelSize: 17
                            elide: Label.ElideRight
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                        Label {
                            text: "Address: " + deviceAddress
                            color: "#9E9E9E"
                            font.pixelSize: 11
                            elide: Label.ElideRight
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                        Label {
                            text: "Voltage: " + deviceValue
                            color: "#9E9E9E"
                            font.pixelSize: 11
                            elide: Label.ElideRight
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                        Label {
                            id: lblDeviceType
                            text: "Type: " + deviceType
                            color: "#9E9E9E"
                            font.pixelSize: 11
                            elide: Label.ElideRight
                            horizontalAlignment: Qt.AlignLeft
                            verticalAlignment: Qt.AlignVCenter
                            Layout.fillWidth: true
                        }
                    }
                }


                Component.onCompleted: {
                    if(deviceType == 1) {
                        lblDeviceType.text = "Type: Ceiling Lamp"
                    } else if(deviceType == 2) {
                        lblDeviceType.text = "Type: Simple(On/Off)"
                    } else if(deviceType == 3) {
                        lblDeviceType.text = "Type: Dimmer(1 color)"
                    } else if(deviceType == 4) {
                        lblDeviceType.text = "Type: Dimmer(Cool-Warm)"
                    } else if(deviceType == 5) {
                        lblDeviceType.text = "Type: Dimmer(RGB)"
                    } else if(deviceType == 6) {
                        lblDeviceType.text = "Type: SmartPlug"
                    } else {
                        lblDeviceType.text = "Type: Unknown"
                    }

                    if(_display === 1) {
                        listDevice.visible = false
                        gridDevice.visible = true
                    }
                    _totalDevice += 1
                    console.log(_totalDevice + "");
                }
            }
            Rectangle {
                anchors {
                    left: parent.left
                    right: parent.right
                    leftMargin: 0
                    rightMargin: 0
                }
                color: "#ECEFF1"
                height: 5
            }

            highlighted: ListView.isCurrentItem
            onClicked: {
                console.log("push data to deviceId: " + deviceId);
                if(deviceType === 1) {
                    stackView.push("qrc:/pages/DeviceDetailType1.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
                else if(deviceType == 2) {
                    stackView.push("qrc:/pages/DeviceDetailType2.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                    deviceController.controlDeviceSimpleLight(
                                deviceId,
                                deviceAddress,
                                _command,
                                _value);
                }
                else if(deviceType == 3) {
                    stackView.push("qrc:/pages/DeviceDetailType3.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
                else if(deviceType == 4) {
                    stackView.push("qrc:/pages/DeviceDetailType4.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
                else if(deviceType == 5) {
                    stackView.push("qrc:/pages/DeviceDetailType5.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
                else if(deviceType == 6) {
                    stackView.push("qrc:/pages/DeviceDetailType6.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
                else {
                    stackView.push("qrc:/pages/DeviceDetailType.qml", {
                                       _deviceId: deviceId,
                                       _deviceaddress: deviceAddress,
                                       _deviceName: deviceName,
                                       _groupname: _groupname})
                }
            }
            onPressAndHold: {
                console.log("onPressAndHold Turn on: " + deviceName);
                _devicename = deviceName;
                _deviceaddress = deviceAddress;
                _deviceid = deviceId;
                popupDeleteDevice.open();
            }

        }

        model: deviceController.listDevice(_groupname)

        Popup {
            id: popupDeleteDevice
            x: 0
            y: parent.height - height
            width: parent.width
            height: 160
            modal: true
            focus: true

            background: Rectangle {
                implicitWidth: parent.width
                implicitHeight: parent.height
                color: "white"

            }

            Item {
                height: parent.height
                width: parent.width

                Label {
                    id: txtTitleDeleteDevice
                    anchors.horizontalCenter: parent.horizontalCenter
                    color: "#EF6C00"
                    text: "[" + _devicename + "]"
                    font.pixelSize: 12
                }

                Rectangle {
                    id: rectDeleteOK
                    width: parent.width
                    height: 50
                    radius: 50
                    border.color: "#EEEEEE"
                    border.width: 1
                    anchors {
                        top: txtTitleDeleteDevice.bottom
                        topMargin: 10
                    }

                    Text {
                        id: btnDeleteOK
                        anchors {
                            centerIn: parent
                        }
                        text: qsTr("Delete")
                        font.pixelSize: 12
                        color: "gray"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            deviceController.deleteDevice(_deviceid, _deviceaddress);
                            popupDeleteDevice.close();
                            _totalDevice -= 1;
                            if(_totalDevice > 0) {
                                itemNotFoundDevice.visible = false
                                listDevice.visible = true
                            }
                            else
                            {
                                itemNotFoundDevice.visible = true
                                listDevice.visible = false
                                gridDevice.visible = false
                            }
                        }
                    }
                }

                Rectangle {
                    id: rectDeleteCancel
                    width: parent.width
                    height: 50
                    radius: 50
                    border.color: "#EEEEEE"
                    border.width: 1
                    anchors {
                        top: rectDeleteOK.bottom
                        topMargin: 10
                    }


                    Text {
                        id: btnDeleteCancel
                        anchors {
                            centerIn: parent
                        }
                        text: qsTr("Cancel")
                        font.pixelSize: 12
                        color: "gray"
                    }
                    MouseArea {
                        anchors.fill: parent
                        onClicked: {
                            popupDeleteDevice.close();
                        }
                    }
                }
            }
        }

        ScrollIndicator.vertical: ScrollIndicator { }
    }

    Item {
        id: itemNotFoundDevice
        height: parent.height
        width: parent.width
        Image {
            id: imgNotFound
            source: "qrc:/images/sad.png"
            anchors.centerIn: parent
        }
        Text {
            anchors.top: imgNotFound.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("Not found!")
            color: "gray"
            font.pixelSize: 13
        }
    }

    Component.onCompleted: {
        if(_totalDevice > 0) {
            itemNotFoundDevice.visible = false
            listDevice.visible = true
        }
        else
        {
            itemNotFoundDevice.visible = true
            listDevice.visible = false

        }
    }


    Popup {
        id: popupAddDevice
        x: 0
        y: parent.height - height
        width: parent.width
        height: 300
        modal: true
        focus: true

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"

        }

        Item {
            height: parent.height
            width: parent.width

            Label {
                id: lblWaringDelete
                text: "(*)Warning: address or device name is NULL"
                anchors.horizontalCenter: parent.horizontalCenter
                color: "red"
                font.pixelSize: 10
                visible: false
            }

            Label {
                id: lblGroupName
                anchors.top: lblWaringDelete.bottom
                text: "[" + _groupname.toUpperCase() + "]"
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#EF6C00"
            }

            TextField {
                id: txtDeviceAddress
                background: Rectangle {
                    radius: 50
                    opacity: 1.0
                    implicitWidth: parent.width
                    implicitHeight: 50
                    border.color: "#ECEFF1"
                    border.width: 1
                }
                placeholderText: "<i>Device address...</i>"
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: lblGroupName.bottom
                anchors.topMargin: 10
                Image {
                    width: 20
                    height: 20
                    source: "qrc:/images/ic_edit.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }
                Component.onCompleted: {
                    if(txtDeviceAddress.text.length === 2)
                    {
                        txtDeviceAddress.text += ":";
                        txtDeviceAddress.text.toUpperCase();
                    }
                }

            }

            TextField {
                id: txtDeviceName
                background: Rectangle {
                    radius: 50
                    opacity: 1.0
                    implicitWidth: parent.width
                    implicitHeight: 50
                    border.color: "#ECEFF1"
                    border.width: 1
                }
                placeholderText: "<i>Device name...</i>"
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: txtDeviceAddress.bottom
                anchors.topMargin: 10
                Image {
                    width: 20
                    height: 20
                    source: "qrc:/images/ic_edit.png"
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.right: parent.right
                    anchors.rightMargin: 10
                }
            }

            ComboBox {
                id: comboDeviceType
                property int styleIndex: -1
                model: [
                    "[1] - Ceiling Lamp",
                    "[2] - Simple (On/Off)",
                    "[3] - Dimmer 1 Color",
                    "[4] - Dimmer Cool-Warm",
                    "[5] - Dimmer RGB",
                    "[6] - SmartPlug"
                ]
                background: Rectangle {
                    radius: 50
                    implicitWidth: parent.width
                    implicitHeight: 50
                    border.color: "#ECEFF1"
                    border.width: 1
                }
                anchors {
                    top: txtDeviceName.bottom
                    topMargin: 10
                    left: parent.left
                    leftMargin: 0
                    right: parent.right
                    rightMargin: 0
                    horizontalCenter: parent.horizontalCenter
                }
                Layout.fillWidth: true
                onCurrentIndexChanged: {
                   _deviceType = currentIndex + 1;
                    console.log("_deviceType: " + _deviceType);
                }
            }

            Rectangle {
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                anchors {
                    top: comboDeviceType.bottom
                    topMargin: 10
                }
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FAFAFA" }
                    GradientStop { position: 1.0; color: "#B0BEC5" }
                }

                Text {
                    id: btnAddDeviceTitle
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Add Device")
                    font.pixelSize: 12
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("action add device");

                        if(txtDeviceAddress.text.trim() === "") {
                            lblWaringDelete.visible = true;
                            lblWaringDelete.text = "(*)Warning: address NULL";
                            return;
                        }
                        else
                        {
                            if(deviceController.checkDeviceExisted(txtDeviceAddress.text.trim()) === true) {
                                lblWaringDelete.visible = true;
                                lblWaringDelete.text = "(*)Warning: device is EXISTED";
                                return;
                            }
                            else
                            {
                                lblWaringDelete.visible = false;
                                lblWaringDelete.text = "";
                            }
                        }

                        if(txtDeviceName.text.trim() === ""){
                            lblWaringDelete.visible = true;
                            lblWaringDelete.text = "(*)Warning: device name NULL";
                            return;
                        }
                        else
                        {
                            lblWaringDelete.visible = false;
                            lblWaringDelete.text = "";
                        }

                        if(txtDeviceAddress.text.trim() !== "" &&
                                txtDeviceName.text.trim() !== "" &&
                                deviceController.checkDeviceExisted(txtDeviceAddress.text.trim()) === false)
                        {
                            deviceController.addDevice(txtDeviceAddress.text.trim(),
                                                       txtDeviceName.text.trim(),
                                                       _groupname.trim(),
                                                       _deviceType);
                            lblWaringDelete.text = "";
                            lblWaringDelete.visible = false;
                            popupAddDevice.close();
                            itemNotFoundDevice.visible = false
                            listDevice.visible = true
                        }
                    }
                }
            }
        }
    }



//    Item {
//        height: 60
//        width: parent.width

//        property bool refresh: state == "pulled" ? true : false

//        Row {
//            spacing: 6
//            anchors.centerIn: parent

//            Image {
//                id: arrow
//                source: "qrc:/images/loading.png"
//                transformOrigin: Item.Center
//                Behavior on rotation { NumberAnimation { duration: 500 } }
//            }

//            Text {
//                id: label
//                anchors.verticalCenter: arrow.verticalCenter
//                text: "Pull to refresh...    "
//                font.pixelSize: 15
//                color: "#999999"
//            }
//        }

//        states: [
//            State {
//                name: "base"; when: listDevice.contentY >= -120
//                PropertyChanges {
//                    target: arrow;
//                    rotation: 180
//                }
//            },
//            State {
//                name: "pulled"; when: listDevice.contentY < -120
//                PropertyChanges { target: label; text: "Release to refresh..." }
//                PropertyChanges { target: arrow; rotation: 0 }
//            }
//        ]
//    }
}
