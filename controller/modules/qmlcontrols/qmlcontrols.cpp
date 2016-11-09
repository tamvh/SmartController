#include <QtQml>
#include <QtGui>
#include <QVariantMap>
#include "qmlcontrols.h"
#include "qmlunit.h"
#include "qmlcss.h"
#include "qmldevice.h"

#include <QtPlugin>
#include <QQuickWindow>
#include <QDebug>

#ifdef Q_OS_IOS
Q_IMPORT_PLUGIN(QtQuickControlsPlugin)
Q_IMPORT_PLUGIN(QtQmlModelsPlugin)
#endif

static QPointer<QmlDevice> deviceInstance;

static QObject* qml_unit_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    QmlUnit *unit = new QmlUnit();
    return unit;
}

static QObject* qml_css_provider(QQmlEngine *engine, QJSEngine *scriptEngine)
{
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);
    QmlCSS *css = new QmlCSS();
    return css;
}

static QObject* qml_device_provider(QQmlEngine* engine, QJSEngine *scriptEngine) {
    Q_UNUSED(engine);
    Q_UNUSED(scriptEngine);

    if (deviceInstance.isNull()) {
        deviceInstance = new QmlDevice();
    }

    QScreen *src = QGuiApplication::screens().at(0); // @TODO: Dynamic update
    deviceInstance->setScreenWidth(src->availableGeometry().width());
    deviceInstance->setScreenHeight(src->availableGeometry().height());

    return deviceInstance.data();
}

void QmlControls::registerTypes()
{
    qmlRegisterSingletonType<QmlUnit>("QmlControls", 0, 1, "Unit", qml_unit_provider);
    qmlRegisterSingletonType<QmlCSS>("QmlControls", 0, 1, "CSS", qml_css_provider);
    qmlRegisterSingletonType<QmlDevice>("QmlControls", 0, 1, "QmlDevice", qml_device_provider);
}


void QmlControls::setupWindow(QQuickWindow *window)
{
    Q_UNUSED(window);
#ifdef Q_OS_IOS
    if (deviceInstance.isNull()) {
        deviceInstance = new QmlDevice();
    }

    deviceInstance->setScreenFillStatusBar(true);

    window->showFullScreen();
#endif
}

#ifdef Q_OS_IOS
bool ios_applicationSetStatusBarStyle(int style);
#endif

void QmlControls::setStatusBarStyle(QmlControls::StatusBarStyle style)
{
    Q_UNUSED(style);

#ifdef Q_OS_IOS
    ios_applicationSetStatusBarStyle(style);
#endif
}
