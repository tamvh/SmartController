#ifndef QMLCONTROLS_QMLDEVICE_H
#define QMLCONTROLS_QMLDEVICE_H

#include <QObject>

/// Device information provider

class QmlDevice : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool screenFillStatusBar READ screenFillStatusBar WRITE setScreenFillStatusBar NOTIFY screenFillStatusBarChanged)
    Q_PROPERTY(int screenWidth READ screenWidth WRITE setScreenWidth NOTIFY screenWidthChanged)
    Q_PROPERTY(int screenHeight READ screenHeight WRITE setScreenHeight NOTIFY screenHeightChanged)

    Q_ENUMS(StatusBarStyle)
public:
    enum StatusBarStyle {
        StatusBarStyleDefault,
        StatusBarStyleLightContent,
        StatusBarStyleBlackTranslucent,
        StatusBarStyleBlackOpaque,
        StatusBarStyleHidden = 100
    };

public:
    QmlDevice(QObject* parent = 0);
    ~QmlDevice();

    /// It is truth if the status bar area should be filled by the application
    bool screenFillStatusBar() const;
    void setScreenFillStatusBar(bool screenFillStatusBar);

    int screenWidth() const;
    void setScreenWidth(int screenWidth);

    int screenHeight() const;
    void setScreenHeight(int screenHeight);

    Q_INVOKABLE void setStatusBarStyle(StatusBarStyle style);
signals:
    void screenFillStatusBarChanged();
    void screenHeightChanged();
    void screenWidthChanged();

private:
    bool m_screenFillStatusBar;
    int m_screenWidth;
    int m_screenHeight;
};

#endif // QMLCONTROLS_QMLDEVICE_H
