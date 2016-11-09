#ifndef DEVICEMANAGER
#define DEVICEMANAGER

#include <QSharedPointer>
#include <vector>

class DeviceInfo;
class DeviceCalendar;
class DeviceLogs;

//! forward declaration of ZDevice
//! support assignment operator
class ZDevice;

//! represent device's current data, state
class ZDeviceData;

//! + Manage list of devices
//! + Manage device's information structure
class DeviceManager : public QObject {
    Q_OBJECT
public:
    DeviceManager(QObject* parent = 0);
    ~DeviceManager();
public:
    void initialize();
public:
    //! @section Device List Management

    int32_t addDevice(ZDevice& device);
    void removeDevice(int32_t deviceId, const QString& remoteAddress);
    std::list<ZDevice>& getDeviceList();
    std::list<ZDevice>& getDeviceList(const QString& groupName);
    ZDevice getDevice(int32_t deviceId);
    ZDevice getDevice(const QString& remoteAddress);

    //! @section Device Profile Management
    //! Manage device's basic properties: Name, Avatar, Type, Address, Id
    void updateDeviceProfile(const ZDevice& device);

    ZDeviceData getDeviceData(int32_t deviceId);
    void updateDeviceData(int32_t deviceId, const ZDeviceData& data);
    void updateDeviceData(int32_t deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar);

    void updateDeviceState(const QString address, const int32_t value);
    int32_t getDeviceState(const QString address);
signals:
    void deviceListChanged();

public slots:
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // DEVICEMANAGER

