#include <QTime>
#include <QDebug>

#include "src/app_commons.h"
#include "src/model/zdevice.h"
#include "src/model/zdevicecalendaritem.h"
#include "src/manager/devicemanager.h"
#include "src/db/devicecalendardb.h"

#include "devicecalendarmanager.h"

class DeviceCalendarManager::Impl {
public:
    Impl() {
        _deviceCalendarDB = std::shared_ptr<DeviceCalendarDB>(new DeviceCalendarDB);
    }
public:
    std::shared_ptr<DeviceCalendarDB> _deviceCalendarDB;
};

DeviceCalendarManager::DeviceCalendarManager()
    : d_ptr(new Impl) {
}

DeviceCalendarManager::~DeviceCalendarManager() {

}

void DeviceCalendarManager::initialize() {
}

void DeviceCalendarManager::addDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar) {
    qDebug() << Q_FUNC_INFO;

    Q_UNUSED(deviceId);
    d_ptr->_deviceCalendarDB.get()->updateCalendarItem(calendar);
}

void DeviceCalendarManager::removeDeviceCalendar(int32_t calendarId) {
    qDebug() << Q_FUNC_INFO << calendarId;
    d_ptr->_deviceCalendarDB.get()->deleteCalendarItem(calendarId);
}

void DeviceCalendarManager::updateDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar) {
    Q_UNUSED(deviceId);
    d_ptr->_deviceCalendarDB.get()->updateCalendarItem(calendar);
}

void DeviceCalendarManager::insertDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar) {
    Q_UNUSED(deviceId);
    d_ptr->_deviceCalendarDB.get()->insertCalendarItem(calendar);
}

ZDeviceCalendarList DeviceCalendarManager::getCalendarItemList() {    
    return d_ptr->_deviceCalendarDB.get()->getCalendarItemList();
}

ZDeviceCalendarList DeviceCalendarManager::getCalendarItemList(int32_t deviceId) {
    return d_ptr->_deviceCalendarDB.get()->getCalendarItemList(deviceId);
}

QString DeviceCalendarManager::getCalendarSummary(int32_t deviceId) {
    qDebug() << Q_FUNC_INFO << "deviceId:" << deviceId;
    QString result  = "Chưa có hẹn giờ";
    QList<ZDeviceCalendarItem> listCalendar = d_ptr->_deviceCalendarDB.get()->getCalendarItemList(deviceId);
    int currentHour = QTime::currentTime().hour();
    int currentMinute = QTime::currentTime().minute();
    for (ZDeviceCalendarItem calendarItem: listCalendar) {
        if ((calendarItem.hour() > currentHour) ||
                ((calendarItem.hour() == currentHour) &&
                 (calendarItem.minute() > currentMinute))) {
            QString resultTmp = "Tự động ";
            resultTmp += calendarItem.autoOn_ ? "bật ":"tắt ";
            resultTmp += "sau ";
            if (calendarItem.hour() <= 9) {
                resultTmp += "0";
            }
            resultTmp += QString::number(calendarItem.hour());
            resultTmp += ":";
            if (calendarItem.minute() <= 9) {
                resultTmp += "0";
            }

            resultTmp += QString::number(calendarItem.minute());
            if (calendarItem.repeartType() == ZDeviceCalendarItem::RepeartTypeEveryDay) {
                resultTmp += " hàng ngày.";
            }
            return resultTmp;
        }
    }
    return result;
}
