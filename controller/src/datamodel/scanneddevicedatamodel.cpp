#include "scanneddevicedatamodel.h"

ScannedDeviceDataModel::ScannedDeviceDataModel(const QString &deviceAddress,
                                               const QString &deviceName,
                                               bool hasLampService):
    address_(deviceAddress),
    name_(deviceName),
    selected_(false),
    hasLampService_(hasLampService)
{
}

ScannedDeviceDataModel::~ScannedDeviceDataModel()
{

}

QHash<int, QByteArray> ScannedDeviceDataModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[ScannedDeviceDataModelRoleAddress] = "deviceAddress";
    roles[ScannedDeviceDataModelRoleName] = "deviceName";
    roles[ScannedDeviceDataModelRoleSelected] = "deviceSelected";
    roles[ScannedDeviceDataModelRoleHasLampService] = "hasLampService";
    return roles;
}

QString ScannedDeviceDataModel::typeName() const
{
    return "scannedDeviceItem";
}

QVariant ScannedDeviceDataModel::data(int role) const
{
    switch (role) {
    case ScannedDeviceDataModelRoleAddress:
        return address_;
    case ScannedDeviceDataModelRoleName:
        return name_;
    case ScannedDeviceDataModelRoleSelected:
        return selected_;
    case ScannedDeviceDataModelRoleHasLampService:
        return hasLampService_;
    default:
        return QVariant();
    }
}

bool ScannedDeviceDataModel::setData(const QVariant& value, int role) {
    if (role == ScannedDeviceDataModelRoleSelected) {
        selected_ = value.toBool();
        return true;
    }

    return false;
}

bool ScannedDeviceDataModel::setItemData(const QMap<int, QVariant> &roles) {
    if (roles.contains(ScannedDeviceDataModelRoleSelected)) {
        selected_ = roles[ScannedDeviceDataModelRoleSelected].toBool();
        return true;
    }

    return false;
}

bool ScannedDeviceDataModel::compare(const QVariant& value) const {
    return (address_.compare(value.toString()) == 0);
}

