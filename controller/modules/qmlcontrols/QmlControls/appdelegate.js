// Global scope
.pragma library

var application    = null;

function rootView(rootView) {
    application.rootView(rootView);
}

function presentView(view) {
    application.presentView(view)
}

function dismissView() {
    application.dismissView();
}

function showLoadingView() {
    application.showLoadingView();
}

function hideLoadingView() {
    application.hideLoadingView();
}

function presentViewComponent(view_component) {
    application.loadComponent(view_component)
}

function setIconMapping(mapping) {
    application.setIconMapping(mapping)
}
