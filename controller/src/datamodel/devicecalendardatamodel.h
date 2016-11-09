#ifndef DEVICECALENDARDATAMODEL_H
#define DEVICECALENDARDATAMODEL_H

#include <zabstractrowdatamodel.h>
#include "src/model/zdevicecalendaritem.h"
//! Represent a calendar item for a device
class DeviceCalendarDataModel : public ZAbstractRowDataModel
{
public:
    DeviceCalendarDataModel(int32_t deviceId, int32_t calendarId, int32_t autoOn, int32_t repeat, int64_t eventTime);
    ~DeviceCalendarDataModel();
    DeviceCalendarDataModel(int32_t deviceId,
                            int32_t calendarId,
                            bool autoOn,
                            int hour,
                            int minute,
                            ZDeviceCalendarItem::RepeartType repeartType,
                            int actionType,
                            QList<QString> repeartItems);

    enum {
        DeviceCalendarDataModelRoleDeviceId = Qt::UserRole + 7000,
        DeviceCalendarDataModelRoleCalendarId,
        DeviceCalendarDataModelRoleAutoOn,
        DeviceCalendarDataModelRoleRepeat,
        DeviceCalendarDataModelRoleHour,
        DeviceCalendarDataModelRoleMinute,
        DeviceCalendarDataModelRoleRepeatMode,
        DeviceCalendarDataModelRoleEventTime,
        DeviceCalendarDataModelRoleTimeText,
        DeviceCalendarDataModelRepeartText,
        DeviceCalendarDataModelActionType,
        DeviceCalendarDataModelRoleStatusText
    };
public:
    static QHash<int, QByteArray> roleNames();
    virtual QString typeName() const override;
    virtual QVariant data(int role) const override;
private:
    int32_t deviceId_;
    int32_t calendarId_;
    bool autoOn_;
    int32_t repeatMode_;
    int64_t eventTime_;

    int m_hour;
    int m_minute;
    QList<QString> m_repeartItems;
    int actionType_;
    ZDeviceCalendarItem::RepeartType m_repeartType;
};

#endif // DEVICECALENDARDATAMODEL_H
