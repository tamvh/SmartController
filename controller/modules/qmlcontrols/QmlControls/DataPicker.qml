import QtQuick 2.0
import QmlControls 0.1

Item {
    id: rootItem
    property alias model: picker.model
    property alias visibleItemCount: picker.pathItemCount
    property int selectedIndex: picker.currentIndex
    property alias currentIndex: picker.currentIndex
    PathView {
        id: picker
        anchors.fill: parent
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.5
        interactive: true
        delegate: digitDelegate
        highlight: digitHighlight
        pathItemCount: 7
//        currentIndex: 2
        property real pathStartX: x + width/2
        path: Path {
            startX: picker.pathStartX
            startY: 0
            PathAttribute { name: "itemZ"; value: 0 }
            PathAttribute { name: "itemAngle"; value: -90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathLine { x: picker.pathStartX; y: picker.height*0.4; }
            PathPercent { value: 0.48; }
            PathLine { x: picker.pathStartX; y: picker.height*0.5; }
            PathAttribute { name: "itemAngle"; value: 0.0; }
            PathAttribute { name: "itemScale"; value: 1.0; }
            PathAttribute { name: "itemZ"; value: 100 }
            PathLine { x: picker.pathStartX; y: picker.height*0.6; }
            PathPercent { value: 0.52; }
            PathLine { x: picker.pathStartX; y: picker.height; }
            PathAttribute { name: "itemAngle"; value: 90.0; }
            PathAttribute { name: "itemScale"; value: 0.5; }
            PathAttribute { name: "itemZ"; value: 0 }
        }
    }

    Component {
        id: digitHighlight
        Rectangle {
            width: parent.width; height: Unit.dp(50);
            color: "lightGray"
        }
    }

    Component {
        id: digitDelegate
        Item {
            id: wrapper
            width: parent.width
            height: Unit.dp(44)

            visible: PathView.onPath

            scale: PathView.itemScale
            z: PathView.itemZ

            property variant rotX: PathView.itemAngle
            transform: Rotation {
                axis { x: 1; y: 0; z: 0 } angle: wrapper.rotX;
                origin { x: wrapper.width/2; y: wrapper.height/2; }
            }

            Text {
                anchors.centerIn: parent
                text: name
                font.pixelSize: Unit.sp(30)
            }
        }
    }
}
