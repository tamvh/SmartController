import QtQuick 2.0

Rectangle {
    id: container
    color: "#20000000"

    ProgressHUD {
        id: hud
        anchors.centerIn: parent
        Component.onCompleted: hud.start()
    }
}
