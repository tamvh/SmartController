#include <map>
#include <list>
#include <QDebug>
#include "src/model/zdevice.h"
#include "src/db/zdevicedb.h"
#include "devicemanager.h"

namespace {
typedef std::map<int32_t, ZDevice> ZDeviceMap;
typedef std::map<QString, ZDevice> ZDeviceMapStr;
typedef ZDeviceMap::iterator ZDeviceMapIterator;
typedef ZDeviceMapStr::iterator ZDeviceMapIteratorStr;
typedef std::list<ZDevice> ZDeviceList;
typedef ZDeviceList::iterator ZDeviceListIterator;
typedef std::map<QString, int32_t> ZDeviceStateMap;
typedef std::map<QString,int32_t>::iterator ZDeviceStateMapIterator;
}

class DeviceManager::Impl {
public:
    ZDeviceMap deviceCollection;
    ZDeviceMapStr deviceCollectionStr;
    ZDeviceList deviceList;
    ZDeviceList deviceListInGroup;
    ZDeviceStateMap deviceStateCollection;
    std::shared_ptr<ZDeviceDB> _deviceDB;

    Impl() {
        qDebug() << Q_FUNC_INFO;
        _deviceDB = std::shared_ptr<ZDeviceDB>(new ZDeviceDB);
    }
};

DeviceManager::DeviceManager(QObject* parent)
    : QObject(parent),
      d_ptr(new Impl) {

}

DeviceManager::~DeviceManager() {

}

void DeviceManager::initialize() {
    qDebug() << Q_FUNC_INFO;
    std::vector<QVariantMap> devicesVector = d_ptr->_deviceDB.get()->getDevices();
    qDebug() << Q_FUNC_INFO << "devicesVector.size():" << devicesVector.size();

    if (devicesVector.size() <= 0) {
        return;
    }
    d_ptr->deviceList.clear();
    d_ptr->deviceCollection.clear();
    for (QVariantMap const& deviceVariant: devicesVector) {
        int deviceId = deviceVariant["deviceId"].toInt();
        QString deviceAddress = deviceVariant["remoteAddress"].toString();
        QString deviceName = deviceVariant["deviceName"].toString();
        QString deviceAvatar = deviceVariant["deviceAvatar"].toString();
        QString groupName = deviceVariant["groupName"].toString();
        int devicetype = deviceVariant["deviceType"].toInt();
        qDebug() << Q_FUNC_INFO << "deviceId:" << deviceId;
        qDebug() << Q_FUNC_INFO << "deviceAddress:" << deviceAddress;
        qDebug() << Q_FUNC_INFO << "deviceName:" << deviceName;
        qDebug() << Q_FUNC_INFO << "groupName:" << groupName;
        ZDevice device(deviceId);
        device.setRemoteAddress(deviceAddress);
        device.setDeviceName(deviceName);
        device.setDeviceAvatar(deviceAvatar);
        device.setGroupName(groupName);
        device.setDeviceType(static_cast<ZDeviceType>(devicetype));
        d_ptr->deviceList.push_back(device);
        d_ptr->deviceCollection[device.deviceId()] = device;
        d_ptr->deviceCollectionStr[device.remoteAddress()] = device;
    }
}

std::list<ZDevice>& DeviceManager::getDeviceList() {
    return d_ptr->deviceList;
}
std::list<ZDevice>& DeviceManager::getDeviceList(const QString& groupName) {
    d_ptr->deviceListInGroup.clear();
    qDebug() << "groupNamegroupName: " + groupName;
    for(ZDevice& itemdevice : d_ptr->deviceList){
        if(itemdevice.groupName().compare(groupName) == 0) {
            int deviceId = static_cast<int>(itemdevice.deviceId());
            QString deviceAddress = itemdevice.remoteAddress();
            QString deviceName = itemdevice.deviceName();
            QString deviceAvatar = itemdevice.deviceAvatar();
            ZDevice device(deviceId);
            device.setRemoteAddress(deviceAddress);
            device.setDeviceName(deviceName);
            device.setDeviceAvatar(deviceAvatar);
            device.setDeviceType(static_cast<ZDeviceType>(itemdevice.deviceType()));
            d_ptr->deviceListInGroup.push_back(device);
        }
    }
    return d_ptr->deviceListInGroup;
}

int32_t DeviceManager::addDevice(ZDevice& device) {
    // add device to db
    int result = d_ptr->_deviceDB.get()->insertDevice(device);
    if (result <= 0) {
        //insertOrReplaceDevice fail
        qDebug() << Q_FUNC_INFO << "addDevice fail, result:" << result;
        return result;
    }

    // update new id
    device.setDeviceId(result);

    const ZDevice& deviceTmp = device;
    d_ptr->deviceCollection.insert(std::pair<int32_t, ZDevice>(result, deviceTmp));
    d_ptr->deviceList.push_back(device);

    // signal new device added
    emit  deviceListChanged();

    return device.deviceId();
}

void DeviceManager::removeDevice(int32_t deviceId, const QString& remoteAddress) {
    // remove from db
    bool result = d_ptr->_deviceDB.get()->removeDevice(deviceId);
    // signal device removed
    if (!result) {
        qDebug() << Q_FUNC_INFO << "removeDevice fail, result:" << result;
    }
    // remove from internal caching
    d_ptr->deviceCollectionStr.erase(remoteAddress);
    d_ptr->deviceCollection.erase(deviceId);
    d_ptr->deviceList.remove(deviceId);

    emit deviceListChanged();
}

ZDevice DeviceManager::getDevice(int32_t deviceId) {
    ZDeviceMapIterator itFind = d_ptr->deviceCollection.find(deviceId);
    if (itFind == d_ptr->deviceCollection.end()) {
        return ZDevice();
    } else {
        return itFind->second;
    }
}

ZDevice DeviceManager::getDevice(const QString& remoteAddress){
    ZDeviceMapIteratorStr itFind = d_ptr->deviceCollectionStr.find(remoteAddress);
    if (itFind == d_ptr->deviceCollectionStr.end()) {
        return ZDevice();
    } else {
        return itFind->second;
    }
}

void DeviceManager::updateDeviceData(int32_t deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar) {
    qDebug() << Q_FUNC_INFO << "deviceId:" << deviceId << ",deviceAddress:" << deviceAddress;

    ZDevice device = d_ptr->deviceCollection[deviceId];
    device.setDeviceName(deviceName);
    device.setDeviceAvatar(deviceAvatar);
    d_ptr->deviceCollection[deviceId] = device;


    d_ptr->deviceList.remove(device);
    d_ptr->deviceList.push_front(device);

    // update from db
    bool result = d_ptr->_deviceDB.get()->updateDevice(device);
    qDebug() << Q_FUNC_INFO << "result:" << result;

    emit deviceListChanged();
}

void DeviceManager::updateDeviceState(const QString address, const int32_t value) {
    qDebug() << Q_FUNC_INFO << "address:" << address << ",value:" << value;
    d_ptr->deviceStateCollection.insert(std::pair<QString, int32_t>(address, value));
    d_ptr->deviceStateCollection[address] = value;

    //emit deviceListChanged();
}

int32_t DeviceManager::getDeviceState(const QString address) {
    qDebug() << Q_FUNC_INFO << "address:" << address;
    ZDeviceStateMapIterator it = d_ptr->deviceStateCollection.find(address);
    if (it == d_ptr->deviceStateCollection.end()) {
        return 0;
    }

    int32_t result = d_ptr->deviceStateCollection.find(address)->second;
    qDebug() << Q_FUNC_INFO << "result:" << result;
    return result;
}
