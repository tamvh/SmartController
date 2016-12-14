#include "app_commons.h"
#include "applicationinfo.h"
#include <QDebug>

DB::UPDatabase *GlobalHandle::getApplicationDB() {
     return ApplicationInfo::instance()->applicationDB();
}

/// this function is needed for calling in commons.pri
DB::UPDatabase *getApplicationDB() {
    return ApplicationInfo::instance()->applicationDB();
}

QString getCurrentUserSession() {
    return "";
}

CommonManager *GlobalHandle::commonManager() {
    return ApplicationInfo::instance()->commonManager();
}

DeviceManager *GlobalHandle::deviceManager() {
    return ApplicationInfo::instance()->deviceManager();
}

GroupManager *GlobalHandle::groupManager() {
    return ApplicationInfo::instance()->groupManager();
}

DeviceCalendarManager *GlobalHandle::deviceCalendarManager() {
    return ApplicationInfo::instance()->deviceCalendarManager();
}

DeviceHardwareService *GlobalHandle::deviceHardwareService()
{
    return ApplicationInfo::instance()->deviceHardwareService();
}

QZXing *GlobalHandle::qzxing() {
    return ApplicationInfo::instance()->qzxing();
}

HttpClient *GlobalHandle::httpClient() {
    return ApplicationInfo::instance()->httclient();
}
