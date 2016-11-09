import QtQuick 2.3
import QtQuick.Controls 1.2
import "appdelegate.js" as AppDelegate
import "res.js" as Resource

ApplicationWindow {
    id: application
    visible: true

    Component.onCompleted: {
        console.debug("application loaded");
        AppDelegate.application = application;
    }

    function showLoadingView() {
        console.debug("start Loading_____");
        loadingView.visible = true;
    }

    function hideLoadingView() {
        console.debug("end Loading_____");
        loadingView.visible = false;
    }

    function loadQmlSource(source) {
        mainLoader.source = source;
    }

    function loadComponent(source_component) {
        mainLoader.sourceComponent = source_component
    }

    function setIconMapping(mapping) {
        Resource.icon_mapping = mapping
    }

    Loader {
        // this component performs deferred loading.
        id: mainLoader
        anchors.fill: parent
        visible: status == Loader.Ready
        //z: 0
    }

    WaitingHUD {
        id: loadingView
        anchors.fill: parent
        visible: false
        MouseArea {
            id:aboveMouse
            anchors.fill: parent
        }
        z: 1
    }
}
