import QtQuick 2.0
import QmlControls 0.1

FocusScope {
    id: root
    width: Unit.dp(250)
    height: Unit.dp(28)

    property SearchBoxStyle style: SearchBoxStyle {}
    signal textChanged(string text);


    Rectangle {
        width: parent.width
        height: parent.height
        color: style.backgroundColor
    }

    Rectangle {
      width: parent.width
      anchors.bottom: parent.bottom
      height: 1
      color: style.bottomLineColor
    }

    FontImage {
        id: searchIcon
        anchors { left: parent.left; leftMargin: Unit.dp(8); verticalCenter: parent.verticalCenter }
        width: Unit.dp(28)
        height: parent.height
        source: style.searchIcon
        iconSize: 22
        color: style.iconColor
    }

    Text {
        id: typeSomething
        anchors.left: searchIcon.right
        anchors.right: parent.right
        anchors.verticalCenter: parent.verticalCenter
        text: "Search..."
        color: "gray"
        font.italic: true
    }

    MouseArea {
        anchors.fill: parent
        onClicked: {
            root.focus = true;
            textInput.forceActiveFocus();
            Qt.inputMethod.show();
        }
    }

    TextInput {
        id: textInput
        anchors {
            left: searchIcon.right;
            leftMargin: 0;
            right: clear.left;
            rightMargin: Unit.dp(8);
            verticalCenter: parent.verticalCenter
        }
        focus: false
        selectByMouse: true
        onTextChanged: {
            root.textChanged(text);
        }
    }

    Button {
        id: clear
        width: Unit.dp(28)
        height: parent.height
        anchors {
            right: parent.right
            rightMargin: Unit.dp(8)
            verticalCenter: parent.verticalCenter
        }
        iconName: style.clearIcon
        iconSize: 22
        iconColor: style.iconColor
        opacity: 0

        onClicked: {
            textInput.text = '';
            root.focus = true;
        }
    }

    states: State {
        name: "hasText"; when: textInput.text != ''
        PropertyChanges { target: typeSomething; opacity: 0 }
        PropertyChanges { target: clear; opacity: 1 }
    }

    transitions: [
        Transition {
            from: ""; to: "hasText"
            NumberAnimation { exclude: typeSomething; properties: "opacity" }
        },
        Transition {
            from: "hasText"; to: ""
            NumberAnimation { properties: "opacity" }
        }
    ]
}
