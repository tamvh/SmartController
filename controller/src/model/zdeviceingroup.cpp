#include "zdeviceingroup.h"

ZDeviceInGroup::ZDeviceInGroup()
{
}

int32_t ZDeviceInGroup::deviceId() const {
    return _deviceiId;
}

void ZDeviceInGroup::setDeviceId(int32_t value) {
    _deviceiId = value;
}

int32_t ZDeviceInGroup::deviceType() const {
    return _deviceType;
}

void ZDeviceInGroup::setDeviceType(int32_t value) {
    _deviceType = value;
}

QString ZDeviceInGroup::slave() const {
    return _slave;
}

void ZDeviceInGroup::setSlave(const QString& value) {
    _slave = value;
}

QString ZDeviceInGroup::deviceName() const {
    return _deviceName;
}

void ZDeviceInGroup::setDeviceName(const QString& value) {
    _deviceName = value;
}

QString ZDeviceInGroup::avatar() const {
    return _avatar;
}

void ZDeviceInGroup::setAvatar(const QString& value) {
    _avatar = value;
}

int32_t ZDeviceInGroup::groupId() const {
    return _groupId;
}

void ZDeviceInGroup::setGroupId(int32_t value) {
    _groupId = value;
}

QString ZDeviceInGroup::groupName() const {
    return _groupName;
}

void ZDeviceInGroup::setGroupName(const QString& value) {
    _groupName = value;
}
