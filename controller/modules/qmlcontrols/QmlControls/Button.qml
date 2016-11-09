import QtQuick 2.0
import QmlControls 0.1

ButtonBase {
    id: button
    property alias iconSize: image.iconSize
    property alias iconName: image.source
    property alias iconColor: image.color
    property int iconHoriontalAlignment : Qt.AlignHCenter;

    width: Unit.dp(32)
    height: Unit.dp(32)
    FontImage {
        id: image
        anchors.verticalCenter: parent.verticalCenter
        height: parent.height
    }

    Component.onCompleted: {
        if (iconHoriontalAlignment == Qt.AlignLeft) {
            image.anchors.left = button.left;
        } else if (iconHoriontalAlignment == Qt.AlignHCenter) {
            image.anchors.horizontalCenter = button.horizontalCenter;
        } else {
            image.anchors.right = button.right;
        }
    }
}

