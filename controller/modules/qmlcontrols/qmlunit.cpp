#include "qmlunit.h"

#ifdef Q_OS_ANDROID
#include <QtAndroidExtras/QAndroidJniObject>
#endif

QmlUnit::QmlUnit(QObject *parent) : QObject(parent),
    screenDensity_(1.0),
    fontScaledDensity_(1.0)
{
#ifdef Q_OS_ANDROID
    QAndroidJniObject activity = QAndroidJniObject::callStaticObjectMethod("org/qtproject/qt5/android/QtNative", "activity", "()Landroid/app/Activity;");
    QAndroidJniObject resource = activity.callObjectMethod("getResources","()Landroid/content/res/Resources;");
    QAndroidJniObject metrics = resource.callObjectMethod("getDisplayMetrics","()Landroid/util/DisplayMetrics;");
    screenDensity_ = metrics.getField<float>("density");
    fontScaledDensity_ = metrics.getField<float>("scaledDensity");
#endif

}

QmlUnit::~QmlUnit()
{

}
