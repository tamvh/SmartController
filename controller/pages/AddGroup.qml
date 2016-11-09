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
    id: pageAddGroup
    title: "Add Group"
    property var valAddGroup
    GroupController
    {
        id: groupController
    }
    Settings {
        id: settings
        property string style: "Universal"
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
        id: btnAddGroup
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
            console.log("btnAddGroup onClicked Turn on")            
            if(txtGroupName.text.trim() === "") {
                lblAlarm.text = "(*) Group name must be NOT NULL";
                lblAlarm.visible = true;
            }
            else
            {
                if(groupController.checkGroupExisted(txtGroupName.text) === true)
                {
                    lblAlarm.text = "(*) This group existed!, re-enter other group name";
                    lblAlarm.visible = true;
                }
                else
                {
                    lblAlarm.visible = false;
                    groupController.addGroup(txtGroupName.text);
                    stackView.push("qrc:/pages/Groups.qml");
                }
            }
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
            text: "Add group"
            font.family: "Helvetica"
            font.pointSize: 16
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            anchors {
                horizontalCenter: parent.horizontalCenter
                verticalCenter: parent.verticalCenter
            }
            color: "#424242"
        }
    }

    Column {
        anchors.fill: parent
        Label {
            id: lblAlarm
            width: parent.width
            wrapMode: Label.Wrap
            horizontalAlignment: Qt.AlignHCenter
            anchors {
                top: txtGroupName.bottom
                topMargin: 20
            }
            visible: false
            text: "(*) This group existed!, re-enter other group name"
            color: "red"
        }

        TextField {
            id: txtGroupName
            height: 60
            width: Screen.width
            placeholderText: "<i>Group Name</i>"
            anchors {
                top: parent.top
                topMargin: 5
                horizontalCenter: parent.horizontalCenter
            }
            background: Rectangle {
                radius: 2
                implicitWidth: Screen.width
                implicitHeight: 60
                border.color: "#ECEFF1"
                border.width: 1
            }
            Image {
                id: name
                width: 20
                height: 20
                source: "qrc:/images/ic_edit.png"
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: parent.right
                anchors.rightMargin: 10
            }
            onTextChanged: {
                console.log("Group name onTextChanged: " + txtGroupName.text);
                if(groupController.checkGroupExisted(txtGroupName.text) === true || txtGroupName.text.trim() === "") {
                    lblAlarm.visible = true;
                    btnAddGroup.visible = false;
                    if(txtGroupName.text.trim() === "")
                    {
                        lblAlarm.text = "(*) Group name must be NOT NULL";
                    }
                    else
                    {
                        lblAlarm.text = "(*) This group existed!, re-enter other group name";
                    }
                }
                else
                {
                    lblAlarm.visible = false;
                    btnAddGroup.visible = true;
                }
            }
        }


    }
}
