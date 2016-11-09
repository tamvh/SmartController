#ifndef DEVICECALENDARMANAGER
#define DEVICECALENDARMANAGER

#include <vector>
#include <QSharedPointer>
class ZDeviceCalendarItem;
namespace {
typedef QList<ZDeviceCalendarItem> ZDeviceCalendarList;
typedef ZDeviceCalendarList::iterator ZDeviceCalendarListIterator;

typedef std::map<int32_t, QList<ZDeviceCalendarItem>> ZDeviceCalendarListMap;
typedef ZDeviceCalendarListMap::iterator ZDeviceCalendarListMapIterator;

typedef std::map<int32_t, ZDeviceCalendarItem> ZDeviceCalendarMap;
typedef ZDeviceCalendarMap::iterator ZDeviceCalendarMapIterator;
}
class ZDeviceCalendarItem;

class DeviceCalendarManager {
public:
    DeviceCalendarManager();
    ~DeviceCalendarManager();
public:
    void initialize();
public:
    void addDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar);
    void removeDeviceCalendar(int32_t calendarId);
    void updateDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar);
    void insertDeviceCalendar(int32_t deviceId, const ZDeviceCalendarItem& calendar);
    std::vector<ZDeviceCalendarItem> getDeviceCalendarList(int32_t deviceId);
    ZDeviceCalendarItem getDeviceCalendar(int32_t deviceId);
    ZDeviceCalendarList getCalendarItemList();
    ZDeviceCalendarList getCalendarItemList(int32_t deviceId);

    QString getCalendarSummary(int32_t deviceId);
private:
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // DEVICECALENDARMANAGER2321


