#include <QDebug>

#include "src/app_commons.h"
#include "src/configuration.h"

#include "zlistdatamodel.h"
#include "src/datamodel/devicedatamodel.h"

#include "src/manager/devicemanager.h"
#include "src/manager/devicecalendarmanager.h"
#include "src/manager/devicehardwareservice.h"
#include "devicelistcontroller.h"
#include "src/manager/bluetooth/bluetoothadvertising.h"


#include <vector>
#include <iostream>
#include <memory>
#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergyconnectionparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
#include <QtCore/qbytearray.h>
#include <QtCore/qcoreapplication.h>
#include <QtCore/qlist.h>
#include <QtCore/qscopedpointer.h>
#include <QtCore/qsharedpointer.h>
#include <QtCore/qtimer.h>
#include <QtCore/qendian.h>
#include <QtCore/qhash.h>
#include <QtCore/qvector.h>

DeviceListController::DeviceListController(QObject *parent) :
    timeoutHelper(NULL),
    timeoutReadDeviceState(NULL),
    QObject(parent),
    deviceList_(new ZListDataModel(this)) {
    deviceList_->registerRoleNames(DeviceDataModel::roleNames());

    DeviceManager *deviceManager = GlobalHandle::deviceManager();
    connect(deviceManager,SIGNAL(deviceListChanged()), this, SLOT(onDeviceListChanged()));

    initialize();
    DeviceHardwareService* deviceHardwareService = GlobalHandle::deviceHardwareService();
    connect(deviceHardwareService, &DeviceHardwareService::updateCharacteristicsSuccessful,
            [this](const QString &remoteAddress, const int value) {
//        DeviceManager *deviceManager = GlobalHandle::deviceManager();
//        int state = !deviceManager->getDeviceState(remoteAddress);
//        this->onChangeBrightSuccess(remoteAddress, state);
        this->onChangeBrightSuccess(remoteAddress, value);
        countRetry = 0;
        currentDeviceAddress = "";
    });
    connect(deviceHardwareService, &DeviceHardwareService::updateCharacteristicsFailed,
            [this](const QString &remoteAddress, const int value) {
//        DeviceManager *deviceManager = GlobalHandle::deviceManager();
//        int state = deviceManager->getDeviceState(remoteAddress);
//        this->onChangeBrightFail(remoteAddress, state);
        qDebug() << Q_FUNC_INFO << "#####################################";
        countRetry++;
        currentDeviceAddress = remoteAddress;
        if (countRetry <= 3 && !remoteAddress.isEmpty() && remoteAddress != "") {
            changeBright(remoteAddress, value);
            return;
        } else {
            countRetry = 0;
            currentDeviceAddress = "";
        }
        this->onChangeBrightFail(remoteAddress, value);
    });
    connect(deviceHardwareService, &DeviceHardwareService::result,
            [this](QString &remoteAddress,
            QString &serviceUuid,
            QString &characteristicsUuid,
            QString &value) {
        Q_UNUSED(remoteAddress);
        Q_UNUSED(serviceUuid);
        qDebug()<<"read characteristics: " << characteristicsUuid;
        qDebug()<<"value: "<<value;

    });
    connect(deviceHardwareService, &DeviceHardwareService::result,
            [this](const QString &remoteAddress,
                   const QString &serviceUuid,
                   const QString &characteristicsUuid,
                   const QString &value) {
        this->onReadDeviceStateSuccess(remoteAddress, serviceUuid, characteristicsUuid, value);
    });
    connect(deviceHardwareService, &DeviceHardwareService::readCharacteristicsFailed,
            [this](const QString &remoteAddress) {
        this->onReadDeviceStateFail(remoteAddress);
    });
}

QAbstractListModel* DeviceListController::deviceList() const {
    return deviceList_;
}

void DeviceListController::initialize() {

    onDeviceListChanged();
//    readDevicesState();
}

//void DeviceListController::turnPlug(const QString deviceAddress, const bool isTurnOn) {
//    qDebug() << Q_FUNC_INFO << "start, address:" << deviceAddress << ", isTurnOn:" << isTurnOn;

//    DeviceHardwareService* deviceHardwareService = GlobalHandle::deviceHardwareService();
//    int value = Configuration::TurnOnLamp;
//    if (!isTurnOn) {
//        value = Configuration::TurnOffLamp;
//    }
//    //deviceHardwareService->updateCharacteristic(deviceAddress, Configuration::ServiceId, Configuration::CharacteristicId, value);
//    deviceHardwareService->readValue(deviceAddress,Configuration::ServiceId, Configuration::CharacteristicId);
//}

void DeviceListController::changeBright(const QString deviceAddress, const int value) {
    qDebug() << Q_FUNC_INFO << "start, address:" << deviceAddress << ", value:" << value;
    DeviceHardwareService* service = GlobalHandle::deviceHardwareService();
    service->updateCharacteristic(deviceAddress,
                                  Configuration::ServiceId,
                                  Configuration::CharacteristicId,
                                  value);


//    //! [Advertising Data]
//    QLowEnergyAdvertisingData advertisingData;
//    advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);
//    advertisingData.setIncludePowerLevel(true);
//    advertisingData.setLocalName("HeartRateServer");
//    advertisingData.setServices(QList<QBluetoothUuid>() << QBluetoothUuid::HeartRate);
//    //! [Advertising Data]

//    //! [Service Data]
//    QLowEnergyCharacteristicData charData;
//    charData.setUuid(QBluetoothUuid::HeartRateMeasurement);
//    charData.setValue(QByteArray(2, 0));
//    charData.setProperties(QLowEnergyCharacteristic::Notify);
//    const QLowEnergyDescriptorData clientConfig(QBluetoothUuid::ClientCharacteristicConfiguration,
//                                                QByteArray(2, 0));
//    charData.addDescriptor(clientConfig);

//    QLowEnergyServiceData serviceData;
//    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
//    serviceData.setUuid(QBluetoothUuid::HeartRate);
//    serviceData.addCharacteristic(charData);
//    //! [Service Data]

//    //! [Start Advertising]
//    const QScopedPointer<QLowEnergyController> leController(QLowEnergyController::createPeripheral());
//    const QScopedPointer<QLowEnergyService> service(leController->addService(serviceData));
//    leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData,
//                                   advertisingData);
//    //! [Start Advertising]

//    //! [Provide Heartbeat]
//    QTimer heartbeatTimer;
//    quint8 currentHeartRate = 60;
//    enum ValueChange { ValueUp, ValueDown } valueChange = ValueUp;
//    const auto heartbeatProvider = [&service, &currentHeartRate, &valueChange]() {
//        QByteArray value;
//        value.append(char(0)); // Flags that specify the format of the value.
//        value.append(char(currentHeartRate)); // Actual value.
//        QLowEnergyCharacteristic characteristic
//                = service->characteristic(QBluetoothUuid::HeartRateMeasurement);
//        Q_ASSERT(characteristic.isValid());
//        service->writeCharacteristic(characteristic, value); // Potentially causes notification.
//        if (currentHeartRate == 60)
//            valueChange = ValueUp;
//        else if (currentHeartRate == 100)
//            valueChange = ValueDown;
//        if (valueChange == ValueUp)
//            ++currentHeartRate;
//        else
//            --currentHeartRate;
//    };
//    QObject::connect(&heartbeatTimer, &QTimer::timeout, heartbeatProvider);
//    heartbeatTimer.start(1000);
//    //! [Provide Heartbeat]

//    auto reconnect = [&leController, advertisingData]() {
//        leController->startAdvertising(QLowEnergyAdvertisingParameters(), advertisingData,
//                                       advertisingData);
//    };
//    QObject::connect(leController.data(), &QLowEnergyController::disconnected, reconnect);

}

void DeviceListController::onDeviceListChanged() {
    DeviceManager* manager = GlobalHandle::deviceManager();
    DeviceCalendarManager* calendarManager = GlobalHandle::deviceCalendarManager();
    std::list<ZDevice>& devices = manager->getDeviceList();

    QList<ZAbstractRowDataModelPtr> list;
    for (ZDevice& d : devices) {
        if (d.deviceId() <= 0) {
            continue;
        }

        int value = manager->getDeviceState(d.remoteAddress());
        QString calendarSummary = calendarManager->getCalendarSummary(d.deviceId());
        ZAbstractRowDataModelPtr item(new DeviceDataModel(
                    d.deviceId(), d.deviceName(), d.remoteAddress(), static_cast<int>(d.deviceType()), value, true, d.deviceAvatar(), calendarSummary));
        list.append(item);
    }

    deviceList_->setListContent(list);
}

//void DeviceListController::onTurnPlugSuccess(const QString address, const bool isTurnOn) {
//    qDebug() << Q_FUNC_INFO << "start, address:" << address << ", isTurnOn:" << isTurnOn;
//    DeviceManager *deviceManager = GlobalHandle::deviceManager();
//    deviceManager->updateDeviceState(address, isTurnOn);
//    emit turnPlugSucess();
//}

//void DeviceListController::onTurnPlugFail(const QString address, const bool isTurnOn) {
//    qDebug() << Q_FUNC_INFO << "start, address:" << address<< ", isTurnOn:" << isTurnOn;
//    emit turnPlugFail();
//}

void DeviceListController::onChangeBrightSuccess(const QString address, const int value) {
    qDebug() << Q_FUNC_INFO << "start, address:" << address << ", value:" << value;
    DeviceManager *deviceManager = GlobalHandle::deviceManager();
    deviceManager->updateDeviceState(address, value);
    emit changeBrightSuccess();
}

void DeviceListController::onChangeBrightFail(const QString address, const int value) {
    qDebug() << Q_FUNC_INFO << "start, address:" << address<< ", value:" << value;
    emit changeBrightFail();
}

void DeviceListController::addToQueueReadDeviceState(ZDevice device) {
    qDebug() << Q_FUNC_INFO << "start.......";
    queueReadDeviceState.enqueue(new ZDevice(device));
}

void DeviceListController::readDeviceState(const ZDevice *device) {
    qDebug() << Q_FUNC_INFO << "start......";
    if (device->remoteAddress().isNull() || device->remoteAddress() == "") {
        return;
    }
    DeviceHardwareService* deviceHardwareService = GlobalHandle::deviceHardwareService();
    deviceHardwareService->readValue(device->remoteAddress(), Configuration::ServiceId, Configuration::CharacteristicId);
}

void DeviceListController::readDevicesState() {
    DeviceManager* manager = GlobalHandle::deviceManager();
    std::list<ZDevice>& devices = manager->getDeviceList();

    for (ZDevice& d : devices) {
        if (d.deviceId() <= 0) {
            continue;
        }

        //Add device to queueReadDeviceState
        for (std::list<ZDevice>::iterator it = devices.begin(); it != devices.end(); it++) {
            addToQueueReadDeviceState(*it);
        }
    }

    processReadDeviceState();
}

void DeviceListController::processReadDeviceState() {
    qDebug() << Q_FUNC_INFO << "start......";
    if (timeoutReadDeviceState != nullptr) {
        timeoutReadDeviceState->stop();
    }

    if (queueReadDeviceState.isEmpty()) {
        onDeviceListChanged();
        emit readDeviceStateFinish();
        return;
    }
    emit startReadDevicesState();
    if (timeoutReadDeviceState == nullptr) {
        timeoutReadDeviceState = new QTimer(this);
    }

    timeoutReadDeviceState->setInterval(READ_DEVICE_STATE_TIMEOUT);
    timeoutReadDeviceState->setSingleShot(true);
    disconnect(timeoutReadDeviceState, SIGNAL(timeout()), 0, 0);
    connect(timeoutReadDeviceState, SIGNAL(timeout()), SLOT(processReadDeviceState()));
    timeoutReadDeviceState->start();

    ZDevice *device = queueReadDeviceState.dequeue();
    readDeviceState(device);
}

void DeviceListController::onReadDeviceStateSuccess(const QString &remoteAddress, const QString &serviceUuid,const QString &characteristicsUuid,const QString &value) {
    DeviceManager *deviceManager = GlobalHandle::deviceManager();
    deviceManager->updateDeviceState(remoteAddress, value.toInt());
    emit readDeviceStateSuccess(remoteAddress, serviceUuid, characteristicsUuid, value);
    processReadDeviceState();
}

void DeviceListController::onReadDeviceStateFail(const QString deviceAddress) {
    emit readDeviceStateFail(deviceAddress);
    processReadDeviceState();
}

void DeviceListController::updateDeviceInfo(const int deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar) {
    qDebug() << Q_FUNC_INFO << "start, deviceId:" << deviceId;
    qDebug() << Q_FUNC_INFO << "start, deviceAddress:" << deviceAddress;
    qDebug() << Q_FUNC_INFO << "start, deviceName:" << deviceName;
    qDebug() << Q_FUNC_INFO << "start, deviceAvatar:" << deviceAvatar;
    DeviceManager* manager = GlobalHandle::deviceManager();
    manager->updateDeviceData(deviceId, deviceAddress, deviceName, deviceAvatar);
}

//void DeviceListController::processChangeBright() {
//    qDebug() << Q_FUNC_INFO;
//    if (stackLampBright.isEmpty()) {
//        timeoutHelper->stop();
//        return;
//    }
//    mutex.lock();
//    ZQueueBright *lampBright = stackLampBright.pop();
//    stackLampBright.clear();
//    mutex.unlock();
//    changeBright(lampBright->getDeviceAddress(), lampBright->getPercentBright());
//}

void DeviceListController::addToStack(const QString deviceAddress, const int percentBright) {
    qDebug() << Q_FUNC_INFO;
    changeBright(deviceAddress, percentBright);
}

