import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import Qt.labs.settings 1.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0
import SmartControls 1.0
import "Common.js" as Global
Page {
    id: pageDeviceDetailType3
    title: "Device Detail"
    property var _deviceId: ""
    property var _deviceName: ""
    property var _deviceaddress: ""
    property var _groupname: ""
    property var _power: 0
    property var _valueBrightnessInc: 1
    property var _valueBrightnessDesc: 2
    Settings {
        id: settings
        property string style: "Universal"
    }

    DeviceController {
        id: deviceController
    }

    header:ToolBar {
        background: Rectangle {
            id: header
            implicitWidth: 100
            implicitHeight: 25
            color: "lightblue"
        }
        RowLayout {
            spacing: 20
            anchors.fill: parent

            ToolButton {
                Image {
                    id:imgBack
                    height: 16
                    width: 16
                    source: "qrc:/images/navigation_previous_item.png"
                    anchors {
                        centerIn: parent
                    }
                }
                ColorOverlay {
                    anchors.fill: imgBack
                    source: imgBack
                    color: "#795548"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        stackView.pop();
                    }
                }
            }


            Label {
                id: titleLabel
                text: _deviceName
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "#795548"
            }

            ToolButton {

            }
        }
    }

    Rectangle {
        id: content
        height: parent.height
        width: parent.width
        color: "lightblue"
        Image {
            id: imgNotFound
            source: "qrc:/images/sad.png"
            anchors.centerIn: parent
        }
        Text {
            id: txtWarning
            text: qsTr("Not found controller!")
            color: "gray"
            anchors {
                top: imgNotFound.bottom
                horizontalCenter: parent.horizontalCenter
            }
        }
    }
}
