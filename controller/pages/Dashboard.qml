import QtQuick.Window 2.2
import QtCharts 2.1
import QtQuick 2.6
import QtQuick.Layouts 1.3
import QtQuick.Controls 2.0
import QtQuick.Controls.Material 2.0
import QtQuick.Controls.Universal 2.0
import QtQml 2.2
import QtQml.Models 2.1
import Qt.labs.settings 1.0
import QtQuick.Controls.Styles 1.4
import Qt.labs.folderlistmodel 2.0
import SmartControls 1.0
import QtQuick.Dialogs 1.2
import QtGraphicalEffects 1.0
import "Common.js" as Global


Page {
    id: pageDashboard
    title: "Dashboard"
    property var _totalGroup: 0
    property var _totalDevice: 0
    property var _listGroup: []
    property var _listDevice: []
    property var _dialogAddDevice: 0
    property var _opacity: 1.1
    property var _groupname: ""
    property var _groupid: -1

    Settings {
        id: settings
        property string style: "Universal"
    }

    GroupController
    {
        id: groupController
    }

    DeviceController {
        id: deviceController
    }

    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 25
        color: "#EEEEEE"
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
                    source: "qrc:/images/listmenu.png"
                    anchors.centerIn: parent
                }
                onClicked: drawer.open();
            }

            Label {
                id: titleLabel
                text: ""
                font.pixelSize: 15
                elide: Label.ElideRight
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
                Layout.fillWidth: true
                color: "white"
            }

            ToolButton {
               Image {
                    height: 16
                    width: 16
                    source: "qrc:/images/notification.png"
                    anchors.centerIn: parent
                }
                MouseArea {
                    onClicked: {
                        stackView.push("qrc:/pages/Notification.qml");
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
        opacity: 0.5
        color: "#FAFAFA"
        height: 60
        width: 60
        radius: 60
        border.color: "#FF9100"
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
                popupAddGroup.open();
            }
            onPressed: {
                rectAddGroup.color = "#EEEEEE";
            }
        }
    }

    Rectangle {
        id: rectStatistic
        width: parent.width
        height: parent.height/7
        color: "#EF6C00"
        anchors {

        }

        Rectangle {
            id: rectTotalGroup
            anchors.right: rectVolte.left
            anchors.rightMargin: 10
            width: parent.height
            height: parent.height
            border.width: 1
            border.color: "white"
            color: "#EF6C00"
            radius: 100
            RowLayout {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                Text {
                    id: txtTotalGroup
                    text: qsTr(_totalGroup + "")
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    text: qsTr("groups")
                    color: "white"
                    font.pixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: txtTotalGroup.bottom
                }
            }
        }

        Rectangle {
            id: rectVolte
            anchors {
                centerIn: parent
            }
            width: parent.height
            height: parent.height
            border.width: 1
            border.color: "white"
            color: "#EF6C00"
            radius: 100
            Text {
                anchors.centerIn: parent
                id: txtVolte
                text: qsTr("10W")
                font.pixelSize: 20
                color: "white"
                horizontalAlignment: Qt.AlignHCenter
                verticalAlignment: Qt.AlignVCenter
            }
        }

        Rectangle {
            id: rectTotalDevice
            anchors.left: rectVolte.right
            anchors.leftMargin: 10
            width: parent.height
            height: parent.height
            border.width: 1
            border.color: "white"
            color: "#EF6C00"
            radius: 100
            RowLayout {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                Text {
                    id: txtTotalDevice
                    text: _totalDevice + ""
                    color: "white"
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                }
                Label {
                    text: qsTr("devices")
                    color: "white"
                    font.pixelSize: 12
                    anchors.horizontalCenter: parent.horizontalCenter
                    anchors.verticalCenter: parent.verticalCenter
                    anchors.top: txtTotalDevice.bottom
                }
            }
        }
    }
    Rectangle {
        id: rectPadding
        anchors {
            top: rectStatistic.bottom
        }
        width: parent.width
        height: 20
        color: "#EF6C00"
    }



    Rectangle {
        id: rectContent
        width: Screen.width
        height: Screen.width/3
        anchors {
            top: rectPadding.bottom
        }

        Image {
            height: parent.height
            width: parent.width
            source: "qrc:/images/bg_smarthome.png"
        }
    }

    Rectangle{
        height: parent.height
        width: parent.width
        color: "#FAFAFA"
        anchors {
            top: rectContent.bottom
            topMargin: 1
            bottom: parent.bottom
            bottomMargin: 2
        }

        GridView {
            id: listGroup
            width: Screen.width;
            height: parent.height
            cellWidth: Screen.width/3; cellHeight: Screen.width/3
            clip: true
            displaced: Transition {
                NumberAnimation { properties: "x,y"; easing.type: Easing.OutQuad }
            }
            model: DelegateModel {
                id: visualModel
                model: groupController.listGroup
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
                        Rectangle {
                            height: 30
                            width: 30
                            color: "white"
                            radius: 30
                            border.width: 0.5
                            border.color: "#EEEEEE"

                            anchors {
                                top: parent.top
                                topMargin: 3
                                right: parent.right
                                rightMargin: 3
                            }
                            Text {
                                id: txtTotalDeviceInGroup
                                text: groupTotalDevice + ""
                                color: "gray"
                                font.pixelSize: 10
                                anchors {
                                    centerIn: parent
                                }
                            }
                        }
                        RowLayout {
                            anchors {
                                horizontalCenter: parent.horizontalCenter
                                verticalCenter: parent.verticalCenter
                            }
                            Image {
                                id: imgGroup
                                source: groupAvatar;
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                            }
                            Text {
                                id: txtGroupName
                                text: groupName;
                                font.pixelSize: 12
                                color: "#9E9E9E"
                                anchors.horizontalCenter: parent.horizontalCenter
                                anchors.verticalCenter: parent.verticalCenter
                                anchors.top: imgGroup.bottom
                            }

                            ColorOverlay {
                                anchors.fill: imgGroup
                                source: imgGroup
                                color: "#795548"
                            }
                        }
                        Component.onCompleted: {
                            _totalGroup += 1;
                            _listGroup.push(groupName);                            
                            _totalDevice += groupTotalDevice;
                        }
                    }

                    MouseArea {
                       anchors.fill: parent
                       onPressed: {
                            icon.color = "#CFD8DC"
                            console.log("onPressed Turn on")

                       }
                       onReleased: {
                           icon.color = "white"
                           console.log("onReleased Turn on")
                       }

                       onClicked: {
//                            icon.color = "white";

                            Global.g_groupName = groupName;
                            console.log("Dashboard onClicked Turn on: " + Global.g_groupName);
                            stackView.push(pageListDevice_component, {_groupname: groupName, _listGroup: _listGroup});
                       }

                       onPressAndHold: {
                           console.log("onPressAndHold Turn on")
                           if(groupType === 1) {
                               popupWarning.open();
                           }
                           else {
                               _groupname = groupName;
                               _groupid = groupId;
                               popupDeleteGroup.open();
                           }
                           icon.color = "white"
                       }
                    }
                }
            }            
        }
    }




    Popup {
        id: popupAddGroup
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
                id: txtWarning
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#EF6C00"
                font.pixelSize: 12
                visible: false
            }

            TextField {
                id: groupname
                background: Rectangle {
                    radius: 50
                    opacity: 1.0
                    implicitWidth: parent.width
                    implicitHeight: 50
                    border.color: "#ECEFF1"
                    border.width: 1
                }
                placeholderText: "<i>Group name...</i>"
                width: parent.width
                anchors.horizontalCenter: parent.horizontalCenter
                anchors.top: txtWarning.bottom
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
            Rectangle {
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                anchors {
                    top: groupname.bottom
                    topMargin: 10
                }
                gradient: Gradient {
                    GradientStop { position: 0.0; color: "#FAFAFA" }
                    GradientStop { position: 1.0; color: "#B0BEC5" }
                }

                Text {
                    id: btnAddGroupTitle
                    anchors {
                        centerIn: parent
                    }
                    text: qsTr("Add Group")
                    font.pixelSize: 12
                    color: "gray"
                }
                MouseArea {
                    anchors.fill: parent
                    onClicked: {
                        console.log("action add group");
                        if(groupname.text.trim() === "")
                        {
                            txtWarning.text = "Field [group name] is NOT NULL";
                            txtWarning.visible = true;
                        }
                        else
                        {
                            if(groupController.checkGroupExisted(groupname.text.trim()) === true) {
                                txtWarning.text = "Group [<i>" + groupname.text.trim() + "</i>] is exited!!!";
                                txtWarning.visible = true;
                            }
                            else {
                                txtWarning.text = "";
                                txtWarning.visible = false;
                                groupController.addGroup(groupname.text);
                                popupAddGroup.close();
                            }
                        }
                    }
                }
            }
        }
    }   





    Popup {
        id: popupDeleteGroup
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
                id: txtTitleDeleteGroup
                anchors.horizontalCenter: parent.horizontalCenter
                color: "#EF6C00"
                text: "[" + _groupname + "]"
            }

            Rectangle {
                id: rectDeleteOK
                width: parent.width
                height: 50
                radius: 50
                border.color: "#EEEEEE"
                border.width: 1
                anchors {
                    top: txtTitleDeleteGroup.bottom
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
                        groupController.deleteGroup(_groupid, _groupname);
                        popupFinishDelete.open();
                        popupDeleteGroup.close();
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
                        popupDeleteGroup.close();
                    }
                }
            }
        }
    }


    Popup {
        id: popupWarning
        x: 5
        y: parent.height - height
        width: parent.width
        height: 80
        modal: true
        focus: true
        opacity: 0.9
        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"            
        }

        Item {

            anchors.centerIn: parent
            Text {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                text: qsTr("Root group, can't delete.")
                font.pixelSize: 13
                color: "#9E9E9E"
            }
        }

        Item {
            Timer {
                interval: 5000; running: true; repeat: true
                onTriggered: {
                    popupWarning.close();
                }
            }
        }
    }

    Popup {
        id: popupFinishDelete
        x: 5
        y: parent.height - height -5
        width: parent.width - 10
        height: 50
        opacity: 0.9
        modal: true
        focus: true
        background: Rectangle {
            radius: 5
            implicitWidth: parent.width
            implicitHeight: parent.height
            color: "white"
            border.color: "#FFCCBC"
            border.width: 1
        }

        Item {

            anchors.centerIn: parent
            Text {
                anchors {
                    horizontalCenter: parent.horizontalCenter
                    verticalCenter: parent.verticalCenter
                }
                text: qsTr("Finish deleted!!!")
                font.pixelSize: 12
                color: "red"
            }
        }

        Item {
            Timer {
                interval: 1000; running: true; repeat: true
                onTriggered: {
                    popupFinishDelete.close();
                }
            }
        }
    }

    Component {
        id: pageListDevice_component
        ListDevice {

        }
    }
}
