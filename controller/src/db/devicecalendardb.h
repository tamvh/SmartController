#ifndef ALARMINFODB_H
#define ALARMINFODB_H

#include <QObject>
#include <memory>
class ZDeviceCalendarItem;
class DeviceCalendarDB
{
public:
    DeviceCalendarDB();
    ~DeviceCalendarDB();
public:
    QList<ZDeviceCalendarItem >getAllCalendarItemList();
    void addCalendarItem(ZDeviceCalendarItem calendarItem);
    void updateCalendarItem(ZDeviceCalendarItem calendarItem);
    void insertCalendarItem(ZDeviceCalendarItem calendarItem);
    void deleteCalendarItem(int calendarId);
    QList<ZDeviceCalendarItem >getCalendarItemList();
    QList<ZDeviceCalendarItem >getCalendarItemList(int32_t deviceId);
private:
    class Private;
    std::shared_ptr<Private> d_ptr;
};

#endif // ALARMINFODB_H
