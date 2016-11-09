#include "src/app_commons.h"
#include "src/configuration.h"

#include "src/datamodel/devicedatamodel.h"
#include "src/model/zdevice.h"
#include "src/manager/devicemanager.h"
#include "src/manager/devicehardwareservice.h"

#include "devicedetailcontroller.h"

DeviceDetailController::DeviceDetailController(QObject* parent):
    QObject(parent)
{
    device = nullptr;
}

int32_t DeviceDetailController::deviceId() const {
    return device->deviceId();
}

QString DeviceDetailController::deviceName() const {
    return device->deviceName();
}

QString DeviceDetailController::remoteAddress() const {
    return device->remoteAddress();
}

QString DeviceDetailController::deviceAvatar() const {
    return device->deviceAvatar();
}

bool DeviceDetailController::deviceState() const {
    return deviceState_;
}

void DeviceDetailController::setDeviceId(int value) {
    if (device != nullptr && device->deviceId() == value) {
        return;
    }

    // get device calendar
    device = new ZDevice(value);
    DeviceManager* manager = GlobalHandle::deviceManager();
    ZDevice d = manager->getDevice(value);
    device->setDeviceAvatar(d.deviceAvatar());
    device->setDeviceName(d.deviceName());
    deviceState_ = manager->getDeviceState(d.remoteAddress())?1:0;

    emit deviceInfoUpdated();
}

void DeviceDetailController::setRemoteAddress(const QString remoteAddress) {
    device->setRemoteAddress(remoteAddress);
}

void DeviceDetailController::setDeviceName(const QString deviceName) {
    device->setDeviceName(deviceName);
}

void DeviceDetailController::setDeviceAvatar(const QString deviceAvatar) {
    device->setDeviceAvatar(deviceAvatar);
}

void DeviceDetailController::initialize()
{

}

void DeviceDetailController::updateDeviceInfo(const int deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar) {
    qDebug() << Q_FUNC_INFO << "start, deviceId:" << deviceId;
    qDebug() << Q_FUNC_INFO << "start, deviceAddress:" << deviceAddress;
    qDebug() << Q_FUNC_INFO << "start, deviceName:" << deviceName;
    qDebug() << Q_FUNC_INFO << "start, deviceAvatar:" << deviceAvatar;
    DeviceManager* manager = GlobalHandle::deviceManager();
    manager->updateDeviceData(deviceId, deviceAddress, deviceName, deviceAvatar);
}

void DeviceDetailController::updateDeviceTime(const int deviceId, const QString deviceAddress) {
    qDebug() << Q_FUNC_INFO << "start, deviceId:" << deviceId;
    qDebug() << Q_FUNC_INFO << "start, deviceAddress:" << deviceAddress;

}

void DeviceDetailController::turnPlug(const QString deviceAddress, const bool isTurnOn) {
    qDebug() << Q_FUNC_INFO << "start, address:" << deviceAddress << ", isTurnOn:" << isTurnOn;

    DeviceHardwareService* deviceHardwareService = GlobalHandle::deviceHardwareService();
    int value = Configuration::TurnOnLamp;
    if (!isTurnOn) {
        value = Configuration::TurnOffLamp;
    }
    deviceHardwareService->updateCharacteristic(deviceAddress, Configuration::ServiceId, Configuration::CharacteristicId, value);
}

void DeviceDetailController::onUpdateDeviceTimeSuccess(const QString deviceAddress) {
    qDebug() << Q_FUNC_INFO << "start, address:" << deviceAddress;
}

void DeviceDetailController::onUpdateDeviceTimeFail(const QString deviceAddress) {
    qDebug() << Q_FUNC_INFO << "start, address:" << deviceAddress;
}
