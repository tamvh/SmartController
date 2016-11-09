#ifndef ZDEVICEDB_H
#define ZDEVICEDB_H

#include <QObject>
#include <memory>

class ZDevice;
class ZDeviceDB
{
public:
    ZDeviceDB();
    ~ZDeviceDB();
public:
    std::vector<QVariantMap> getDevices();
    std::vector<QVariantMap> getDevices(const QString& groupName);
    ZDevice getLatestDevice();
    ZDevice getDevice(const QString deviceAddress);
    int insertDevice(ZDevice& device);
    bool updateDevice(ZDevice& device);
    bool removeDevice(int32_t deviceId);
private:
    class Private;
    std::shared_ptr<Private> d_ptr;
};

#endif // ZDEVICEDB_H
