#ifndef DEVICECALENDARCONTROLLER_H
#define DEVICECALENDARCONTROLLER_H

#include <QObject>
#include <QAbstractListModel>
#include "src/model/zdevicecalendaritem.h"

class ZListDataModel;

//! Controller for device's calendar management
//! + Add calendar item
//! + Update calendar item
//! + Remove calendar item
class DeviceCalendarController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int deviceId READ deviceId WRITE setDeviceId NOTIFY deviceInfoUpdated)
    Q_PROPERTY(QString deviceName READ deviceName NOTIFY deviceInfoUpdated)
    Q_PROPERTY(QString deviceAvatar READ deviceAvatar NOTIFY deviceInfoUpdated)
    Q_PROPERTY(int deviceState READ deviceState NOTIFY deviceStateChanged)
//    Q_PROPERTY(QAbstractListModel* calendarList READ calendarList CONSTANT)

public:

//    Q_ENUM(ZDeviceCalendarItem::RepeartType)
    explicit DeviceCalendarController(QObject *parent = 0);
public slots:
    Q_INVOKABLE void deleteDeviceCalendar(int calendarId, int row);
    Q_INVOKABLE void updateDeviceCalendar(int calendarId,
                                          int deviceId,
                                          int hour,
                                          int minute,
                                          int repeartMode,
                                          int actionType,
                                          QList<QString> repeartItems,
                                          bool autoOn);

    Q_INVOKABLE void insertDeviceCalendar(int deviceId,
                                          int hour,
                                          int minute,
                                          int repeartMode,
                                          int actionType,
                                          QList<QString> repeartItems,
                                          bool autoOn);




signals:
    void deviceInfoUpdated();
    void deviceStateChanged();

public slots:
    void removeCalendar(int calendarId);
    void updateCalendar();
    void addCalendar();
//    QAbstractListModel* calendarList() const;
    QAbstractListModel* calendarList(int deviceId) const;

private:
    int32_t deviceId() const;
    QString deviceName() const;
    QString deviceAvatar() const;
    int32_t deviceState() const;
    void setDeviceId(int32_t value);
    void initializeCalendarList();
private:
    int32_t deviceId_;
    QString deviceName_;
    QString deviceAvatar_;
    int32_t deviceState_;
    ZListDataModel* calendarList_;
};

#endif // DEVICECALENDARCONTROLLER_H
