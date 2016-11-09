import QtQuick 2.0
import QmlControls 0.1
import QmlControls.Material 0.1
import SmartLamp 1.0
import BLE 0.1 as QmlBLE
import "Main"

Item {
//    property var navigationItem : NavigationItem {
//                   title : "Choose Coffee"
//    }
    property var navigationItem : NavigationItem {
        titleSize: Unit.dp(18)
        height: Unit.dp(48)
        titleColor: "#ffffff"
        barTintColor: "#222222"
        backButtonVisible: false

        title : "Choose Coffee"
        rightBarButtonItem: Button {
            id: settingButton
            iconName: "tool"
            iconSize: 25
            iconColor: "white"
            width: Unit.dp(44)
            height: Unit.dp(44)
            anchors {
                top: parent.top
                right: parent.right
                margins: 5
            }
            onClicked: {
                console.log("onClicked Settings");
                //lampController.connectType
                console.log("onClicked Settings, lampController.connectType: ", lampController.connectType);
                console.log("onClicked Settings, lampController.connectType: ", LampController.ConnectTypeBluetooth);
                if (lampController.connectType == LampController.ConnectTypeBluetooth) {
                    console.log("onClicked Settings, show bluetoothDeviceList_component");
                    navigation.push(bluetoothDeviceList_component)
                    return
                }
                if (lampController.connectType == LampController.ConnectTypeWifi) {
                    wificonfigurationView.show()
                    return
                }
            }
        }
        leftBarButtonItem: Item {
            width: Unit.dp(42)
            height: Unit.dp(32)
            Image {
                id: appIcon
                width: Unit.dp(32)
                height: Unit.dp(32)
                source: Qt.resolvedUrl("images/ic_launcher.png")
                anchors {
                    right: parent.right
                    verticalCenter: parent.verticalCenter
                }
            }
        }
    }

    QtObject {
        id: setting
        property color cupColor: "#4B3621"
        property color cupBackgroundColor: "#ecf0f1"
    }

    Text {
        id: title
        text: "What do you want to make?"
        width: navigationItem.width
        height: Unit.dp(30)

        color: "#4e4e4e"
        verticalAlignment: Text.AlignVCenter
        horizontalAlignment: Text.AlignHCenter

        font { family: "Myriad Pro"; pixelSize: Unit.sp(20)}
        visible: false
    }

    Column {
        spacing: Unit.dp(10)
        anchors {
            top: parent.top
            topMargin: Unit.dp(20)
            left: parent.left
            leftMargin: Unit.dp(30)
        }
        width: Unit.dp(120)
        z: 1
        Image {
            width: parent.width
            height: parent.width
            source: Qt.resolvedUrl("images/espresso.png")
            MouseArea {
                anchors.fill: parent
                onClicked: lampController.makeCoffee(lampController.CoffeeTypeEspresso)
            }
        }

        Text {
            width: parent.width
            text: qsTr("Espresso Cup")
            color: "#ffbb33"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font { family: "Myriad Pro"; pixelSize: Unit.sp(16); bold: true}
        }
    }
    Column {
        spacing: Unit.dp(10)
        anchors {
            top: parent.top
            topMargin: Unit.dp(100)
            right: parent.right
            rightMargin: Unit.dp(10)
        }
        width: Unit.dp(200)
//        ActionButton {
//            elevation: 0
//            backgroundColor: CSS.colorPumpkin
//            width: parent.width
//            height: parent.width
//            FontImage {
//                iconSize: 60
//                anchors.fill: parent
//                source: "big-cup"
//                color: setting.cupColor
//            }
//            onClicked:  {
//                lampController.makeCoffee(lampController.CoffeeTypeLong)
//            }
//        }
        Image {
            width: parent.width
            height: parent.width
            source: Qt.resolvedUrl("images/large_cup.png")

            MouseArea {
                anchors.fill: parent
                onClicked: lampController.makeCoffee(lampController.CoffeeTypeLong)
            }
        }
        Text {
            width: parent.width
            text: qsTr("Long Cup")
            color: "#000000"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font { family: "Myriad Pro"; pixelSize: Unit.sp(16); bold: true}
        }
    }
    Column {
        spacing: Unit.dp(10)
        anchors {
            top: parent.top
            topMargin: Unit.dp(280)
            left: parent.left
            leftMargin: Unit.dp(20)
        }
        width: Unit.dp(140)
//        ActionButton {
//            elevation: 0
//            backgroundColor: CSS.colorOrange
//            width: parent.width
//            height: parent.width
//            FontImage {
//                iconSize: 60
//                anchors.fill: parent
//                source: "normal-cup"
//                color: setting.cupColor
//            }
//            onClicked:  {
//                lampController.makeCoffee(lampController.CoffeeTypeNormal)
//            }
//        }
        Image {
            width: parent.width
            height: parent.width
            source: Qt.resolvedUrl("images/normal_cup.png")

            MouseArea {
                anchors.fill: parent
                onClicked: lampController.makeCoffee(lampController.CoffeeTypeNormal)
            }
        }
        Text {
            width: parent.width
            text: qsTr("Normal Cup")
            color: "#0099cc"
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font { family: "Myriad Pro"; pixelSize: Unit.sp(16); bold: true}
        }
    }


    MaterialButton {
        width: Unit.dp(120)
        height: Unit.dp(40)
        elevation: 1
        anchors {
            bottom: parent.bottom
            right: parent.right
            rightMargin: Unit.dp(16)
            bottomMargin: Unit.dp(16)
        }
        backgroundColor: CSS.colorClouds
        FontImage {
            id: connectIcon
            width: Unit.dp(30)
            height: Unit.dp(30)
            iconSize: 20
            anchors {
                verticalCenter: parent.verticalCenter
                left: parent.left
            }
            source: "connect"
            color: CSS.colorMidnightBlue
        }
        Text {
            id: connectTypeText
            text: qsTr("connection: Cloud")
            font.pixelSize: Unit.sp(12)
            verticalAlignment: Text.AlignVCenter

            anchors {
                verticalCenter: parent.verticalCenter
                left: connectIcon.right
                right: parent.right
            }
        }
        onClicked:  {
            if (!chooseConnect.visible) {
                chooseConnect.show()
            } else {
                chooseConnect.close()
            }
        }
    }

    MaterialButton {
        id: connectTypeButton
        width: Unit.dp(128)
        height: Unit.dp(40)
        anchors {
            bottom: parent.bottom
            left: parent.left
            leftMargin: Unit.dp(16)
            bottomMargin: Unit.dp(16)
        }
        elevation: 1
        FontImage {
            id: coffeeMachineIcon
            width: Unit.dp(30)
            height: Unit.dp(30)
            anchors {
                left: parent.left
                leftMargin: Unit.dp(10)
                verticalCenter: parent.verticalCenter
            }
            source: "coffee-machine"
            color: "#4B3621"
//            visible: LampController.hasBluetoothCurrentAddress
        }
        Text {
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignRight
            text:LampController.isConnect? "Connect":"Disconnect"
            font.pixelSize: Unit.sp(12)
            anchors {
                top: parent.top
                right: parent.right
                leftMargin: Unit.dp(16)
                rightMargin: Unit.dp(16)
                bottom: parent.bottom
                left: coffeeMachineIcon.right
            }
        }

        backgroundColor: LampController.isConnect?CSS.colorPeterRiver:"red"
        onClicked: {
            lampController.connectButtonClicked()
        }
    }

    LampController {
        id: lampController
        onConnectTypeChanged:  {
            setConnectTypeText(connectType)
            settingButton.visible = (connectType == LampController.ConnectTypeBluetooth || connectType == LampController.ConnectTypeWifi)
        }
        onShowScanBluetoothDevice: {
            navigation.push(bluetoothDeviceList_component)
        }
        onShowSnackbarMessage: {
            snackbar.open(message)
        }
    }
    Snackbar {
        id: snackbar
    }
    Component.onCompleted: {
        setConnectTypeText(lampController.connectType)
    }

    function setConnectTypeText(connectType) {
        switch(connectType) {
        case LampController.ConnectTypeWifi:
            connectTypeText.text = "Wifi"
            break;
        case LampController.ConnectTypeBluetooth:
            connectTypeText.text = "Bluetooth"
            break;
        default:
            connectTypeText.text = "Cloud"
            break;
        }
    }

    ChooseConnect {
        id: chooseConnect
        connectType: lampController.connectType
        onResultConnectType:  {
            lampController.connectType = connectType
        }
    }
    WifiConfigurationView {
        id: wificonfigurationView

    }

    Component {
        id: bluetoothDeviceList_component
        QmlBLE.BluetoothDeviceList {

        }
    }
    Component {
        id: wificonfiguration_component
        WifiConfigurationView {

        }
    }
}

