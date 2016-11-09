#include "devicedatamodel.h"

DeviceDataModel::DeviceDataModel(int deviceId,
                                 const QString &deviceName,
                                 const QString &deviceIcon,
                                 const QString &deviceValue,
                                 const QString &sectionName):
    m_id(deviceId),
    m_name(deviceName),
    m_icon(deviceIcon),
    m_value(deviceValue),
    m_section(sectionName)
{

}

DeviceDataModel::~DeviceDataModel()
{

}

QHash<int, QByteArray> DeviceDataModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[DeviceDataModelRoleId] = "deviceId";
    roles[DeviceDataModelRoleName] = "deviceName";
    roles[DeviceDataModelRoleIcon] = "deviceIcon";
    roles[DeviceDataModelRoleValue] = "deviceValue";
    roles[DeviceDataModelRoleSection] = "deviceSection";
    return roles;
}
QString DeviceDataModel::typeName() const
{
    return "deviceItem";
}
QVariant DeviceDataModel::data(int role) const
{
    switch (role) {
    case DeviceDataModelRoleId:
        return m_id;
    case DeviceDataModelRoleName:
        return m_name;
    case DeviceDataModelRoleIcon:
        return m_icon;
    case DeviceDataModelRoleValue:
        return m_value;
    case DeviceDataModelRoleSection:
        return m_section;
    default:
        return QVariant();
    }
}
