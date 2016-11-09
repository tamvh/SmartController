#include "qmldevice.h"
#include "qmlcontrols.h"

QmlDevice::QmlDevice(QObject* parent) : QObject(parent)
{
    m_screenFillStatusBar = false;
    m_screenWidth = -1;
    m_screenHeight = -1;
}

QmlDevice::~QmlDevice()
{

}

bool QmlDevice::screenFillStatusBar() const
{
    return m_screenFillStatusBar;
}

void QmlDevice::setScreenFillStatusBar(bool screenFillStatusBar)
{
    m_screenFillStatusBar = screenFillStatusBar;
    emit screenFillStatusBarChanged();
}

int QmlDevice::screenWidth() const
{
    return m_screenWidth;
}

void QmlDevice::setScreenWidth(int screenWidth)
{
    m_screenWidth = screenWidth;
    emit screenHeightChanged();
}

int QmlDevice::screenHeight() const
{
    return m_screenHeight;
}

void QmlDevice::setScreenHeight(int screenHeight)
{
    m_screenHeight = screenHeight;
    emit screenHeightChanged();
}

#ifdef Q_OS_IOS
void ios_applicationSetStatusBarHidden(bool hidden);
#endif

void QmlDevice::setStatusBarStyle(StatusBarStyle style)
{
    if (style == StatusBarStyleHidden) {
#ifdef Q_OS_IOS
        ios_applicationSetStatusBarHidden(true);
#endif
    } else {
#ifdef Q_OS_IOS
        ios_applicationSetStatusBarHidden(false);
#endif
        QmlControls::setStatusBarStyle((QmlControls::StatusBarStyle)style);
    }
}

