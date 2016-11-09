import QtQuick 2.0
import QmlControls 0.1

ListView {
    id: root
    property int latency: 600
    property int rotationThreshold: 135
    property string pullMessageString: qsTr("Kéo xuống để làm mới")
    property string releaseMessageString: qsTr("Thả ra để làm mới")
    property alias foreColor: pullImage.color

    clip: true

    signal refreshEvent

    Item {
        property bool __puller: false

        id: pull
        width: parent.width
        opacity: -pullImage.rotation / parent.rotationThreshold
        y: -(parent.contentY + pullImage.height + labelRow.spacing)

        Row {
            id: labelRow
            anchors.left: parent.left
            anchors.leftMargin: spacing
            spacing: pullImage.width / 2
            width: pullImage.width + pullLabel.width + spacing

            FontImage {
                id: pullImage
                smooth: true
                source: "refresh"
                iconSize: 32
                color: "#2c3e50"
                width: Unit.dp(40)
                height: Unit.dp(40)
                rotation: 2 * 360 * root.contentY / root.height
                onRotationChanged: {
                    if (pullImage.rotation < -root.rotationThreshold) {
                        if (!pullTimer.running && !pull.__puller)
                            pullTimer.restart()
                    } else if (pullImage.rotation > -root.rotationThreshold) {
                        if (!pullTimer.running && pull.__puller)
                            pullTimer.restart()
                    }
                }

                Timer {
                    id: pullTimer
                    interval: root.latency

                    onTriggered: {
                        if (pullImage.rotation < -root.rotationThreshold)
                            pull.__puller = true
                        else
                            pull.__puller = false
                    }
                }
            }

            Text {
                id: pullLabel
                text: {
                    if (pull.__puller)
                        return root.releaseMessageString

                    return root.pullMessageString
                }
                color: root.foreColor
                anchors.verticalCenter: parent.verticalCenter
            }
        }
    }

    onMovementEnded: {
        if (pull.__puller)
            root.refreshEvent()

        pull.__puller = false
        pullTimer.stop()
    }
}
