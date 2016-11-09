
import QtQuick 2.3
import QtQuick.Layouts 1.1
import QtQuick.Controls 1.2 as Controls
import QtQuick.Window 2.0
import Material 0.2
import QmlControls 0.1
import "js/flaticon.js" as UIIcon

ApplicationWindow {
    title: "Application Name"
    visibility: "Maximized"
    visible: true
//    visibility: "FullScreen"
    theme.primaryColor: "red"

    initialPage: mainpage

    MainPage {
        id: mainpage
    }

    function init(context) {
    }

    function showLoadingView() {
        cyclicColorProgress.visible = true
        shadow.visible = true
    }

    function hideLoadingView() {
        cyclicColorProgress.visible = false
        shadow.visible = false
    }
    Rectangle {
        id: shadow
        anchors.fill: parent
        color: "#00000000"
        visible: false

        MouseArea {
            anchors.fill: parent
            onClicked: {

            }
        }
    }

    ProgressCircle {
        id: cyclicColorProgress
        visible: false
        width: Unit.dp(40)
        height: Unit.dp(40)
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        SequentialAnimation {
            running: true
            loops: Animation.Infinite

            ColorAnimation {
                from: "red"
                to: "blue"
                target: cyclicColorProgress
                properties: "color"
                easing.type: Easing.InOutQuad
                duration: 2400
            }

            ColorAnimation {
                from: "blue"
                to: "green"
                target: cyclicColorProgress
                properties: "color"
                easing.type: Easing.InOutQuad
                duration: 1560
            }

            ColorAnimation {
                from: "green"
                to: "#FFCC00"
                target: cyclicColorProgress
                properties: "color"
                easing.type: Easing.InOutQuad
                duration:  840
            }

            ColorAnimation {
                from: "#FFCC00"
                to: "red"
                target: cyclicColorProgress
                properties: "color"
                easing.type: Easing.InOutQuad
                duration:  1200
            }
        }
    }
}

//ApplicationWindowEx {
//    id: app
//    property bool clientSideDecorations: false

//    property color button: "#ffa726"
//    property color subText: "#485C68"
//    property color highlight: CSS.colorGreenSea
//    property color navigationBarColor: highlight
//    property color normal: "#6c6c6c"

//    OverlayLayer {
//        id: dialogOverlayLayer
//        objectName: "dialogOverlayLayer"
//    }

//    OverlayLayer {
//        id: tooltipOverlayLayer
//        objectName: "tooltipOverlayLayer"
//    }

//    OverlayLayer {
//        id: overlayLayer
//    }
//    visibility: "Maximized"
////    width: Units.dp(320)
////    height: Units.dp(568)
//    function init(context) {
//        showMainView()
//    }

//    function showMainView() {
//        AppDelegate.presentViewComponent(mainWindow)
//    }

//    Component {
//        id: mainWindow
//        MainWindow {
//        }
//    }

//    Component.onCompleted: {
//        AppDelegate.setIconMapping(UIIcon.map)
//        if (clientSideDecorations)
//            flags |= Qt.FramelessWindowHint

//        Units.pixelDensity = Qt.binding(function() {
//            return Screen.pixelDensity
//        });

//        Device.type = Qt.binding(function () {
//            var diagonal = Math.sqrt(Math.pow((Screen.width/Screen.pixelDensity), 2) +
//                    Math.pow((Screen.height/Screen.pixelDensity), 2)) * 0.039370;

//            if (diagonal >= 3.5 && diagonal < 5) { //iPhone 1st generation to phablet
//                Units.multiplier = 1;
//                return Device.phone;
//            } else if (diagonal >= 5 && diagonal < 6.5) {
//                Units.multiplier = 1;
//                return Device.phablet;
//            } else if (diagonal >= 6.5 && diagonal < 10.1) {
//                Units.multiplier = 1;
//                return Device.tablet;
//            } else if (diagonal >= 10.1 && diagonal < 29) {
//                return Device.desktop;
//            } else if (diagonal >= 29 && diagonal < 92) {
//                return Device.tv;
//            } else {
//                return Device.unknown;
//            }
//        });

//        // Nasty hack because singletons cannot import the module they were declared in, so
//        // the grid unit cannot be defined in either Device or Units, because it requires both.
//        Units.gridUnit = Qt.binding(function() {
//            return Device.type === Device.phone || Device.type === Device.phablet
//                    ? Units.dp(48) : Device.type == Device.tablet ? Units.dp(56) : Units.dp(64)
//        })
//    }
//}
