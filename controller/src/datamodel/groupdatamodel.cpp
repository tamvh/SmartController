#include "groupdatamodel.h"


GroupDataModel::GroupDataModel(int32_t id,
                               const QString& name,
                               const QString& avatar,
                               int32_t type,
                               int32_t totalDevice)
    : _id(id),
      _name(name),
      _avatar(avatar),
      _type(type),
      _totalDevice(totalDevice)
{

}

GroupDataModel::~GroupDataModel()
{

}

QHash<int, QByteArray> GroupDataModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[GroupModelRoleId] = "groupId";
    roles[GroupModelRoleName] = "groupName";
    roles[GroupModelRoleAvatar] = "groupAvatar";
    roles[GroupModelRoleType] = "groupType";
    roles[GroupModelRoleTotalDevice] = "groupTotalDevice";
    return roles;
}

QString GroupDataModel::typeName() const
{
    return "groupItem";
}

QVariant GroupDataModel::data(int role) const
{
    switch (role) {
    case GroupModelRoleId:
        return _id;
    case GroupModelRoleName:
        return _name;
    case GroupModelRoleAvatar:
        return _avatar;
    case GroupModelRoleType:
        return _type;
    case GroupModelRoleTotalDevice:
        return _totalDevice;
    default:
        return QVariant();
    }
}

bool GroupDataModel::setData(const QVariant& value, int role) {
    return false;
}

bool GroupDataModel::setItemData(const QMap<int, QVariant> &roles) {
    return false;
}

bool GroupDataModel::compare(const QVariant& value) const {
    return (_name.compare(value.toString()) == 0);
}
