
#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQuickWindow>
#include <QQmlContext>

#include "applicationinfo.h"
#include <QDebug>

int main(int argc, char* argv[])
{
    QGuiApplication app(argc,argv);
    ApplicationInfo appInfo;
    appInfo.applicationStartup();
    appInfo.start("qrc:///qmls/main.qml");

    return app.exec();
}
