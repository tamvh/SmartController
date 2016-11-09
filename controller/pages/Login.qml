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
    id: pageLogin
    title: "Login"
    Settings {
        id: settings
        property string style: "Universal"
    }   

    Rectangle {
        id: root
        height: parent.height
        width: parent.width
    }
}
