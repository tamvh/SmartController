#ifndef QMLCONTROLS_QMLCSS_H
#define QMLCONTROLS_QMLCSS_H

#include <QObject>
#include <QColor>
#include <QHash>

class QmlCSS : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QColor defaultColor READ defaultColor CONSTANT)
    Q_PROPERTY(QColor pressedColor READ pressedColor CONSTANT)

    Q_PROPERTY(QColor colorTurquoise READ colorTurquoise CONSTANT)
    Q_PROPERTY(QColor colorGreenSea READ colorGreenSea CONSTANT)
    Q_PROPERTY(QColor colorEmerald READ colorEmerald CONSTANT)
    Q_PROPERTY(QColor colorNephritis READ colorNephritis CONSTANT)
    Q_PROPERTY(QColor colorPeterRiver READ colorPeterRiver CONSTANT)
    Q_PROPERTY(QColor colorBelizeHole READ colorBelizeHole CONSTANT)
    Q_PROPERTY(QColor colorAmethyst READ colorAmethyst CONSTANT)
    Q_PROPERTY(QColor colorWisteria READ colorWisteria CONSTANT)
    Q_PROPERTY(QColor colorWetAsphalt READ colorWetAsphalt CONSTANT)
    Q_PROPERTY(QColor colorMidnightBlue READ colorMidnightBlue CONSTANT)
    Q_PROPERTY(QColor colorSunFlower READ colorSunFlower CONSTANT)
    Q_PROPERTY(QColor colorOrange READ colorOrange CONSTANT)
    Q_PROPERTY(QColor colorCarrot READ colorCarrot CONSTANT)
    Q_PROPERTY(QColor colorPumpkin READ colorPumpkin CONSTANT)
    Q_PROPERTY(QColor colorAlizarin READ colorAlizarin CONSTANT)
    Q_PROPERTY(QColor colorPomeGranate READ colorPomeGranate CONSTANT)
    Q_PROPERTY(QColor colorConcrete READ colorConcrete CONSTANT)
    Q_PROPERTY(QColor colorAsbestos READ colorAsbestos CONSTANT)
    Q_PROPERTY(QColor colorClouds READ colorClouds CONSTANT)
    Q_PROPERTY(QColor colorSilver READ colorSilver CONSTANT)

    Q_PROPERTY(QColor loginBackgroundColor READ loginBackgroundColor CONSTANT)
    Q_PROPERTY(QColor loginButtonBackgroundColor READ loginButtonBackgroundColor CONSTANT)
    Q_PROPERTY(QColor loginButtonDisableBackgroundColor READ loginButtonDisableBackgroundColor CONSTANT)
    Q_PROPERTY(QColor loginButtonPressedBackgroundColor READ loginButtonPressedBackgroundColor CONSTANT)
    Q_PROPERTY(QColor loginTextColor READ loginTextColor CONSTANT)
    Q_PROPERTY(QColor buttonDefaultBackgroundColor READ buttonDefaultBackgroundColor CONSTANT)
    Q_PROPERTY(QColor buttonDefaultDisableBackgroundColor READ buttonDefaultDisableBackgroundColor CONSTANT)
    Q_PROPERTY(QColor buttonDefaultPressedBackgroundColor READ buttonDefaultPressedBackgroundColor CONSTANT)
    Q_PROPERTY(QColor buttonDefaultTextColor READ buttonDefaultTextColor CONSTANT)

    Q_PROPERTY(QColor buttonColor READ buttonColor CONSTANT)
    Q_PROPERTY(QColor appLogoColor READ appLogoColor CONSTANT)
    Q_PROPERTY(QString appLogo READ appLogo CONSTANT)
public:
    explicit QmlCSS(QObject *parent = 0);
public:
    QColor defaultColor() const;
    QColor pressedColor() const;

    QColor colorTurquoise() const;
    QColor colorGreenSea() const;
    QColor colorEmerald() const;
    QColor colorNephritis() const;
    QColor colorPeterRiver() const;
    QColor colorBelizeHole() const;
    QColor colorAmethyst() const;
    QColor colorWisteria() const;
    QColor colorWetAsphalt() const;
    QColor colorMidnightBlue() const;
    QColor colorSunFlower() const;
    QColor colorOrange() const;
    QColor colorCarrot() const;
    QColor colorPumpkin() const;
    QColor colorAlizarin() const;
    QColor colorPomeGranate() const;
    QColor colorConcrete() const;
    QColor colorAsbestos() const;
    QColor colorClouds() const;
    QColor colorSilver() const;

    QColor loginBackgroundColor() const;
    QColor loginButtonBackgroundColor() const;
    QColor loginButtonDisableBackgroundColor() const;
    QColor loginButtonPressedBackgroundColor() const;
    QColor loginTextColor() const;
    QColor buttonDefaultBackgroundColor() const;
    QColor buttonDefaultDisableBackgroundColor() const;
    QColor buttonDefaultPressedBackgroundColor() const;
    QColor buttonDefaultTextColor() const;
    QColor buttonColor() const;
    QColor appLogoColor() const;
    QString appLogo() const;
signals:

public slots:
private:
};

#endif // QMLCONTROLS_QMLCSS_H
