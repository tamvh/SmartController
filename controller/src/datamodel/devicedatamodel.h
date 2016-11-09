#ifndef DEVICEDATAMODEL_H
#define DEVICEDATAMODEL_H

#include "zabstractrowdatamodel.h"

//! DeviceDataModel has following fields:
//! + deviceId: id of device
//! + remoteAddress: BLE address
//! + deviceName: name of device
//! + currentState: current power state: 1 = On, 0 = Off
//! + calendarSummary: summary for all calendar items which device has.
//!     ex: "Tự động BẬT hàng ngày lúc 08:00 AM"
//!     ex: "Tự động TẮT lúc 10:00 PM"
//!     ex: "Chưa có lịch hẹn giờ"
class DeviceDataModel: public ZAbstractRowDataModel
{
public:
    DeviceDataModel(int deviceId,
                    const QString &deviceName,
                    const QString &deviceAddress,
                    const int &deviceType,
                    const int &deviceValue,
                    bool hasLampService,
                    const QString &deviceAvatar,
                    const QString calendarSummary);
    ~DeviceDataModel();
    enum {
        PlugDataModelRoleName = Qt::UserRole + 6000,
        PlugDataModelRoleAddress,
        PlugDataModelRoleType,
        PlugDataModelRoleValue,
        PlugDataModelRoleAvatar,
        PlugDataModelRoleId,
        PlugDataModelRoleHasLampService,
        PlugDataModelRoleCalendarSummary,
        PlugDataModelRoleShowLoading
    };
public:
    static QHash<int, QByteArray> roleNames();
    virtual QString typeName() const override;
    virtual QVariant data(int role) const override;
private:
    int m_id;
    QString m_name;
    QString m_icon;
    QString m_address;
    int m_deviceType;
    int m_value;
    QString deviceAvatar_;    
    bool m_hasLampService;
    bool m_showLoading;
    QString m_calendarSummary;
};

#endif // DEVICEDATAMODEL_H
