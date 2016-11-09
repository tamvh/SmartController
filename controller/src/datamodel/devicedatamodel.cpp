#include "devicedatamodel.h"

DeviceDataModel::DeviceDataModel(int deviceId,
                                 const QString &deviceName,
                                 const QString &deviceAddress,
                                 const int &deviceType,
                                 const int &deviceValue,
                                 bool hasLampService,
                                 const QString &deviceAvatar,
                                 const QString calendarSummary):
    m_id(deviceId),
    m_name(deviceName),
    m_address(deviceAddress),
    m_deviceType(deviceType),
    m_value(deviceValue),
    deviceAvatar_(deviceAvatar),
    m_hasLampService(hasLampService),
    m_calendarSummary(calendarSummary)
{
}

DeviceDataModel::~DeviceDataModel()
{

}

QHash<int, QByteArray> DeviceDataModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[PlugDataModelRoleId] = "deviceId";
    roles[PlugDataModelRoleName] = "deviceName";
    roles[PlugDataModelRoleAddress] = "deviceAddress";
    roles[PlugDataModelRoleType] = "deviceType";
    roles[PlugDataModelRoleValue] = "deviceValue";
    roles[PlugDataModelRoleAvatar] = "deviceAvatar";
    roles[PlugDataModelRoleHasLampService] = "hasLampService";
    roles[PlugDataModelRoleCalendarSummary] = "calendarSummary";
    return roles;
}
QString DeviceDataModel::typeName() const
{
    return "deviceItem";
}
QVariant DeviceDataModel::data(int role) const
{
    switch (role) {
    case PlugDataModelRoleId:
        return m_id;
    case PlugDataModelRoleName:
        return m_name;
    case PlugDataModelRoleAddress:
        return m_address;
    case PlugDataModelRoleType:
        return m_deviceType;
    case PlugDataModelRoleValue:
        return m_value;
    case PlugDataModelRoleAvatar:
        return deviceAvatar_;
    case PlugDataModelRoleHasLampService:
        return QVariant::fromValue(m_hasLampService);
    case PlugDataModelRoleCalendarSummary:
        return m_calendarSummary;
    default:
        return QVariant();
    }
}
