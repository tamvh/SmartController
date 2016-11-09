#include <QDebug>
#include <QSharedPointer>

#include "src/app_commons.h"

#include "src/datamodel/scanneddevicedatamodel.h"
#include "src/model/zdevice.h"
#include "src/manager/devicescannerservice.h"
#include "src/manager/devicemanager.h"
#include "zlistdatamodel.h"

#include "devicescanningcontroller.h"

DeviceScanningController::DeviceScanningController(QObject *parent)
    : QObject(parent),
      scanningState_(0),
      deviceList_(new ZListDataModel(this)),
      scannerService_(new DeviceScannerService(this))
{
    deviceList_->registerRoleNames(ScannedDeviceDataModel::roleNames());
    connect(scannerService_, &DeviceScannerService::scanningStarted,
            this, &DeviceScanningController::onScanningStarted);
    connect(scannerService_, &DeviceScannerService::scanningFinished,
            this, &DeviceScanningController::onScanningFinished);
    connect(scannerService_, &DeviceScannerService::foundDevice,
            this, &DeviceScanningController::onFoundDevice);
}

int DeviceScanningController::scanningState() const {
    return scanningState_;
}

QAbstractListModel* DeviceScanningController::deviceList() const {
    return deviceList_;
}

void DeviceScanningController::startScanDevices() {
    qDebug()<<"______"<<Q_FUNC_INFO;

    if (scanningState_ != 0) {
        qDebug() << "SCANNING: is in-progress. Skip!";
        return;
    }

    deviceList_->clear();

    scanningState_ = 1;
    emit scanningStateChanged();

    // start scanning
    scannerService_->startScanning();
}

void DeviceScanningController::stopScanDevices() {
    qDebug()<<"______"<<Q_FUNC_INFO;
    scanningState_ = 0;
    scannerService_->stopScanning();
}

void DeviceScanningController::selectDevice(const QString& remoteAddress) {
    for (int i = 0; i < deviceList_->items().size(); ++i) {
        ScannedDeviceDataModel *scaneDevice = (ScannedDeviceDataModel *)deviceList_->items().at(i).data();
        QString remoteAddress_ = scaneDevice->data(ScannedDeviceDataModel::ScannedDeviceDataModelRoleAddress).toString();
        if (remoteAddress == remoteAddress_) {

            QString deviceName = scaneDevice->data(ScannedDeviceDataModel::ScannedDeviceDataModelRoleName).toString();
            ZDevice device(-1);
            device.setDeviceName(deviceName);
            device.setRemoteAddress(remoteAddress);
            device.setDeviceType(ZDeviceType::BLEPlug);
            GlobalHandle::deviceManager()->addDevice(device);
            return;
        }
    }
}

void DeviceScanningController::onScanningStarted() {
    scanningState_ = 1;
    emit scanningStateChanged();
}

void DeviceScanningController::onScanningFinished() {
    scanningState_ = 0;
    emit scanningStateChanged();
}

void DeviceScanningController::onFoundDevice(const QString& remoteAddress, const QString& deviceName, bool hasLampService) {
    for (int i = 0; i < deviceList_->items().size(); ++i) {
        ScannedDeviceDataModel *scaneDevice = (ScannedDeviceDataModel *)deviceList_->items().at(i).data();
        QString remoteAddress_ = scaneDevice->data(ScannedDeviceDataModel::ScannedDeviceDataModelRoleAddress).toString();
        if (remoteAddress == remoteAddress_) {
            ZAbstractRowDataModelPtr device(new ScannedDeviceDataModel(remoteAddress, deviceName, hasLampService));
            deviceList_->replacedItem(device, i);
            return;
        }
    }

    ZAbstractRowDataModelPtr device(new ScannedDeviceDataModel(remoteAddress, deviceName, hasLampService));
    deviceList_->addItem(device);
}
