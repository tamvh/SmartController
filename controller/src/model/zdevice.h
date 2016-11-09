#ifndef ZDEVICE_H
#define ZDEVICE_H

#include <cstdint>
#include <memory>
#include <vector>
#include <QString>

enum class ZDeviceType {
    BLEPlug = 1,
    BLELamp = 2
};

//! Data structure for a device
class ZDevice
{
public:
    ZDevice();
    ZDevice(const int32_t& deviceId);
    ZDevice(const ZDevice& other);
    ZDevice& operator=(const ZDevice& other);
    bool operator==(const ZDevice& other) const;
    bool operator==(const int32_t deviceId) const;

    int32_t deviceId() const;
    void setDeviceId(int32_t value);

    QString remoteAddress() const;
    void setRemoteAddress(const QString& remoteAddress);

    QString deviceName() const;
    void setDeviceName(const QString& deviceName);

    QString deviceAvatar() const;
    void setDeviceAvatar(const QString& value);

    QString groupName() const;
    void setGroupName(const QString& value);

    ZDeviceType deviceType() const;
    void setDeviceType(const ZDeviceType& deviceType);
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

inline bool operator==(const ZDevice &a1, const int32_t &a2)
{ return a1.deviceId() == a2; }
inline bool operator==(const int32_t &a2, const ZDevice &a1)
{ return a1.deviceId() == a2; }


#endif // ZDEVICE_H
