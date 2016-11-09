import QtQuick 2.4
import Material 0.2 as Material
import Material.ListItems 0.1 as ListItem
import QmlControls 0.1
import QtQuick.Layouts 1.1
import QtQuick.Controls.Styles 1.0
/*!
   \qmltype BottomActionSheet
   \inqmlmodule Material

   \brief Represents a bottom sheet displaying a list of actions with an optional title.

 */
BottomSheet {
    id: bottomSheet

    property string title
    implicitHeight: title !== "" ? header.height + grid.height + action.height
                                 : grid.height + action.height

    signal itemsSelected(string result)
    signal cancel()

    function checkMonToFri() {
        chkMon.checkedState = Qt.Checked
        chkTue.checkedState = Qt.Checked
        chkWed.checkedState = Qt.Checked
        chkThu.checkedState = Qt.Checked
        chkFri.checkedState = Qt.Checked
        chkSat.checkedState = Qt.Unchecked
        chkSun.checkedState = Qt.Unchecked
    }

    function checkAll() {
        chkMon.checkedState = Qt.Checked
        chkTue.checkedState = Qt.Checked
        chkWed.checkedState = Qt.Checked
        chkThu.checkedState = Qt.Checked
        chkFri.checkedState = Qt.Checked
        chkSat.checkedState = Qt.Checked
        chkSun.checkedState = Qt.Checked
    }

    function unCheckAll() {
        chkMon.checkedState = Qt.Unchecked
        chkTue.checkedState = Qt.Unchecked
        chkWed.checkedState = Qt.Unchecked
        chkThu.checkedState = Qt.Unchecked
        chkFri.checkedState = Qt.Unchecked
        chkSat.checkedState = Qt.Unchecked
        chkSun.checkedState = Qt.Unchecked
    }

    Rectangle {
        id: content
        width: parent.width
        height: title !== "" ? header.height + grid.height + action.height
                             : grid.height + action.height

        MouseArea {
            anchors.fill: grid
            onClicked: {
                console.log("Grid onclick.........................")
            }
        }

        ListItem.Subheader {
            id: header
            anchors {
                top: content.top
            }
            text: title
            visible: title !== ""
            height: Unit.dp(48)
            style: "subheading"
            backgroundColor: "white"
            elevation: grid.atYBeginning ? 0 : 1
            fullWidth: true
            z: 2
        }

        Column {
            id: grid
            width: parent.width
            height: 7 * Unit.dp(48)
            anchors {
                top: content.top
                topMargin: title!== ""?Unit.dp(48):0
            }

//            rowSpacing: Unit.dp(0)
//            columnSpacing: Unit.dp(0)
//            columns: 1

            Rectangle {
                id: mon
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: mon
                    onClicked: {
                        chkMon.checkedState= chkMon.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkMon
                    text: "Monday"
                    darkBackground: false
                }
            }

            Rectangle {
                id: tue
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: tue
                    onClicked: {
                        chkTue.checkedState= chkTue.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkTue
                    text: "Tuesday"
                    darkBackground: false
                }
            }
            Rectangle {
                id: wed
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: wed
                    onClicked: {
                        chkWed.checkedState= chkWed.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkWed
                    text: "Wednesday"
                    darkBackground: false
                }
            }

            Rectangle {
                id: thu
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: thu
                    onClicked: {
                        chkThu.checkedState= chkThu.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkThu
                    text: "Thursday"
                    darkBackground: false
                }
            }

            Rectangle {
                id: fri
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: fri
                    onClicked: {
                        chkFri.checkedState= chkFri.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkFri
                    text: "Friday"
                    darkBackground: false
                }
            }

            Rectangle {
                id: sat
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: sat
                    onClicked: {
                        chkSat.checkedState= chkSat.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkSat
                    text: "Saturday"
                    darkBackground: false
                }
            }

            Rectangle {
                id: sun
                width: grid.width
                height: Unit.dp(48)
                MouseArea {
                    anchors.fill: sun
                    onClicked: {
                        chkSun.checkedState=  chkSun.checked?Qt.Unchecked:Qt.Checked
                    }
                }

                CheckBox {
                    id: chkSun
                    text: "Sunday"
                    darkBackground: false
                }
            }
        }

        Rectangle {
            id: action
            width: parent.width
            height: Unit.dp(48)
            anchors {
                top: grid.bottom
                topMargin: Unit.dp(8)
            }

            Row {
                id: row
                width: parent.width
                height: Unit.dp(48)
                spacing: Unit.dp(0)

                anchors {
                    horizontalCenter: parent.horizontalCenter
                }

                Material.Button {
                    id: btnCancel
                    width: parent.width/2
                    height: Unit.dp(48)
                    text: "Cancel"
                    elevation: 0

                    onClicked: {
                        cancel()
                        bottomSheet.close()
                    }
                }

                Rectangle {
                    width: 1
                    height: Unit.dp(48)
                    color: "black"
                }

                Material.Button {
                    id: btnDone
                    width: parent.width/2
                    height: Unit.dp(48)
                    text: "OK"
                    elevation: 0

                    onClicked: {
                        var result= "";
                        result+= chkMon.checked?"Mon ":"";
                        result+= chkTue.checked?"Tue ":"";
                        result+= chkWed.checked?"Wed ":"";
                        result+= chkThu.checked?"Thu ":"";
                        result+= chkFri.checked?"Fri ":"";
                        result+= chkSat.checked?"Sat ":"";
                        result+= chkSun.checked?"Sun ":"";
                        itemsSelected(result);
                        bottomSheet.close()
                    }
                }
            }


            Rectangle {
                id: separate
                width: parent.width
                height: 1
                color: "black"
            }

        }
    }
}
