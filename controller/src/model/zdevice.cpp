
#include "zdevice.h"

class ZDevice::Impl {
public:
    int32_t deviceId;
    QString remoteAddress;
    QString deviceName;
    QString deviceAvatar;
    QString groupName;
    ZDeviceType deviceType;
};

ZDevice::ZDevice() :
    d_ptr(new Impl)
{

}

ZDevice::ZDevice(const int32_t& deviceId) :
    d_ptr(new Impl)
{
    d_ptr->deviceId = deviceId;
}

ZDevice::ZDevice(const ZDevice& other) :
    d_ptr(other.d_ptr)
{

}

ZDevice& ZDevice::operator=(const ZDevice& other) {
    d_ptr = other.d_ptr;
    return *this;
}

bool ZDevice::operator==(const ZDevice& other) const {
    return d_ptr->deviceId == other.deviceId();
}

bool ZDevice::operator==(const int32_t deviceId) const {
    return d_ptr->deviceId == deviceId;
}

int32_t ZDevice::deviceId() const {
    return d_ptr->deviceId;
}

void ZDevice::setDeviceId(int32_t value) {
    d_ptr->deviceId = value;
}

QString ZDevice::remoteAddress() const {
    return d_ptr->remoteAddress;
}

void ZDevice::setRemoteAddress(const QString& remoteAddress) {
    d_ptr->remoteAddress = remoteAddress;
}

QString ZDevice::deviceName() const {
    return d_ptr->deviceName;
}

void ZDevice::setDeviceName(const QString& deviceName) {
    d_ptr->deviceName = deviceName;
}

QString ZDevice::deviceAvatar() const {
    return d_ptr->deviceAvatar;
}

void ZDevice::setDeviceAvatar(const QString& value) {
    d_ptr->deviceAvatar = value;
}

QString ZDevice::groupName() const {
    return d_ptr->groupName;
}

void ZDevice::setGroupName(const QString& value) {
    d_ptr->groupName = value;
}

ZDeviceType ZDevice::deviceType() const {
    return d_ptr->deviceType;
}

void ZDevice::setDeviceType(const ZDeviceType& deviceType) {
    d_ptr->deviceType = deviceType;
}
