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
import "Common.js" as Global

Page {
    id: pageGroups
    title: "List Group"
    Settings {
        id: settings
        property string style: "Universal"
    }
    property var _listGroup: []
    GroupController
    {
        id: groupController
    }
    background: Rectangle {
        implicitWidth: 100
        implicitHeight: 25
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
                contentItem: Image {
                    id: imgAddGroup
                    fillMode: Image.Pad
                    horizontalAlignment: Image.AlignHCenter
                    verticalAlignment: Image.AlignVCenter
                    source: "qrc:/images/ic_addgroup.png"
                }
                ColorOverlay {
                    anchors.fill: imgAddGroup
                    source: imgAddGroup
                    color: "white"
                }
                onClicked: {
                    console.log("Add group")
                    stackView.push("qrc:/pages/AddGroup.qml");
                }
            }
        }
    }


    GridView {
        id: listGroup
        width: Screen.width; height: parent.height
        cellWidth: Screen.width/2; cellHeight: Screen.width/1.8        
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

                width: Screen.width/2; height: Screen.width/1.8
                drag.target: icon

                Rectangle {
                    id: icon
                    width: Screen.width/2; height: Screen.width/1.8
                    anchors {
                        left: parent.left
                        leftMargin: 1
                        top: parent.top
                        topMargin: 1
                        horizontalCenter: parent.horizontalCenter;
                        verticalCenter: parent.verticalCenter
                    }
                    border.color: "#EEEEEE"
                    border.width: 1
                    color: "#FFF"
                    radius: 1
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
                        _listGroup.push(groupName);
                    }

                }

                MouseArea {
                   anchors.fill: parent
                   onPressed: {
                        icon.color = "#EEEEEE"
                        console.log("onPressed Turn on")
                   }
                   onClicked: {
                        icon.color = "#FFF";
                        console.log("onClicked Turn on");
                        stackView.push(pageListDevice_component, {_groupname: groupName, _listGroup: _listGroup});
                   }

                   onPressAndHold: {
                       console.log("onPressAndHold Turn on")
                       if(groupType != 1) {
                            messageDialogRootGroup.show(qsTr("[" + groupName + "] is root group, CAN'T DELETE"))
                       }
                       icon.color = "#FFF"
                   }
                }


                MessageDialog {
                    id: messageDialogNormalGroup
                    icon: StandardIcon.Critical
                    title: qsTr("Do you want to delete group?")
                    standardButtons: StandardButton.Yes | StandardButton.No

                    function show(caption) {
                        messageDialogNormalGroup.text = caption;
                        messageDialogNormalGroup.open();
                    }
                    onNo: {
                        console.log("action don't delete")
                    }
                    onYes: {
                        console.log("action delete")
                        groupController.deleteGroup(groupId)
                    }
                }

                MessageDialog {
                    id: messageDialogRootGroup
                    icon: StandardIcon.Critical
                    title: qsTr("Warning!")
                    standardButtons: StandardButton.Yes

                    function show(caption) {
                        messageDialogRootGroup.text = caption;
                        messageDialogRootGroup.open();
                    }
                }
            }
        }
    }

    Item {
        height: 60
        width: parent.width

        property bool refresh: state == "pulled" ? true : false

        Row {
            spacing: 6
            height: childrenRect.height
            anchors.centerIn: parent

            Text {
                id: label
                anchors.verticalCenter: arrow.verticalCenter
                text: "Pull to refresh...    "
                font.pixelSize: 10
                color: "#4E342E"
            }

        }

        states: [
            State {
                name: "base"; when: listGroup.contentY <= -80
                PropertyChanges { target: arrow; rotation: 180 }
            },
            State {
                name: "pulled"; when: listGroup.contentY > -80
                PropertyChanges { target: label; text: "" }
                PropertyChanges { target: arrow; rotation: 0 }
            }
        ]
    }



    Component {
        id: pageListDevice_component
        ListDevice {

        }
    }
}
