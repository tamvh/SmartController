import QtQuick.Window 2.2
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQml.Models 2.1
import Qt.labs.settings 1.0
import QtGraphicalEffects 1.0

Page {
    id: pageSync
    title: "Sync"
    Settings {
        id: settings
        property string style: "Universal"
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


    Column {
        spacing: 40
        anchors.fill: parent

        Label {
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            text: "[Sync] This function not support"
        }

        BusyIndicator {
            readonly property int size: Math.min(pane.availableWidth, pane.availableHeight) / 5
            width: size
            height: size
            anchors.horizontalCenter: parent.horizontalCenter
        }
    }
    Button {
        id: scanButton
        height: 50

        anchors {
            left: parent.left
            leftMargin: 0
            right: parent.right
            rightMargin: 0
            bottom: parent.bottom
            bottomMargin: 0
        }

        onClicked: {
            console.log("onClicked Turn on")

        }
        Image {
            id: icon1
            width: 30
            height: 30
            anchors {
                right: buttonTitle.left
                rightMargin: 10
                verticalCenter: parent.verticalCenter
            }
            source: "qrc:/images/menu_sync.png"
        }
        Text {
            id: buttonTitle
            text: "SYNC DATA"
            font.family: "Helvetica"
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: "white"
        }
    }
}
