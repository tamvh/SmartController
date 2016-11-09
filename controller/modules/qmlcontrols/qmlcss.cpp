#include <QDebug>

#include "qmlcss.h"

QmlCSS::QmlCSS(QObject *parent) :
    QObject(parent)
{
}

QColor QmlCSS::defaultColor() const
{
    return QColor(0x3498db);
}

QColor QmlCSS::pressedColor() const
{
    return QColor(0x2980b9);
}

QColor QmlCSS::colorTurquoise() const
{
    return QColor(0x1abc9c);
}

QColor QmlCSS::colorGreenSea() const
{
    return QColor(0x16a085);
}

QColor QmlCSS::colorEmerald() const
{
    return QColor(0x2ecc71);
}

QColor QmlCSS::colorNephritis() const
{
    return QColor(0x27ae60);
}

QColor QmlCSS::colorPeterRiver() const
{
    return QColor(0x3498db);
}

QColor QmlCSS::colorBelizeHole() const
{
    return QColor(0x2980b9);
}

QColor QmlCSS::colorAmethyst() const
{
    return QColor(0x9b59b6);
}

QColor QmlCSS::colorWisteria() const
{
    return QColor(0x994eb8);
}

QColor QmlCSS::colorWetAsphalt() const
{
    return QColor(0x34495e);
}

QColor QmlCSS::colorMidnightBlue() const
{
    return QColor(0x2c3e50);
}

QColor QmlCSS::colorSunFlower() const
{
    return QColor(0xf1c40f);
}

QColor QmlCSS::colorOrange() const
{
    return QColor(0xf39c12);
}

QColor QmlCSS::colorCarrot() const
{
    return QColor(0xe67e22);
}

QColor QmlCSS::colorPumpkin() const
{
    return QColor(0xd35400);
}

QColor QmlCSS::colorAlizarin() const
{
    return QColor(0xe74c3c);
}

QColor QmlCSS::colorPomeGranate() const
{
    return QColor(0xc0392b);
}

QColor QmlCSS::colorConcrete() const
{
    return QColor(0x95a5a6);
}

QColor QmlCSS::colorAsbestos() const
{
    return QColor(0x7f8c8d);
}

QColor QmlCSS::colorClouds() const
{
    return QColor(0xecf0f1);
}

QColor QmlCSS::colorSilver() const
{
    return QColor(0xbdc3c7);
}

QColor QmlCSS::loginBackgroundColor() const
{
    return colorMidnightBlue();
}

QColor QmlCSS::loginButtonBackgroundColor() const
{
    return colorPeterRiver();
}

QColor QmlCSS::loginButtonDisableBackgroundColor() const
{
    return colorSilver();
}

QColor QmlCSS::loginButtonPressedBackgroundColor() const
{
    return colorBelizeHole();
}

QColor QmlCSS::loginTextColor() const
{
    return QColor(Qt::white);
}

QColor QmlCSS::buttonDefaultBackgroundColor() const
{
    return colorPeterRiver();
}

QColor QmlCSS::buttonDefaultDisableBackgroundColor() const
{
    return colorSilver();
}

QColor QmlCSS::buttonDefaultPressedBackgroundColor() const
{
    return colorBelizeHole();
}

QColor QmlCSS::buttonDefaultTextColor() const
{
    return QColor(Qt::white);
}

QColor QmlCSS::buttonColor() const
{
    return QColor(Qt::white);
}

QColor QmlCSS::appLogoColor() const
{
    return QColor(0xF1C40F);
}

QString QmlCSS::appLogo() const
{
    return "fa-paw";
}
