#include <QTimer>
#include <QDebug>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>

#include "src/configuration.h"
#include "devicescannerservice.h"

class DeviceScannerService::DeviceScannerServicePrivate {
public:
    DeviceScannerServicePrivate() :
        isScanning(false)
    {
    }
    ~DeviceScannerServicePrivate() {
    }

public:
    bool isScanning;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QList<QString> discoveredDevices;
};

DeviceScannerService::DeviceScannerService(QObject* parent) :
    QObject(parent),
    d_ptr(new DeviceScannerServicePrivate())
{
    Q_D(DeviceScannerService);
    d->discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);
    connect(d->discoveryAgent, SIGNAL(error(QBluetoothDeviceDiscoveryAgent::Error)),
            this, SLOT(onScanningDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error)));
    connect(d->discoveryAgent, &QBluetoothDeviceDiscoveryAgent::deviceDiscovered,
            this, &DeviceScannerService::onScanningDeviceDiscovered);
    connect(d->discoveryAgent, &QBluetoothDeviceDiscoveryAgent::finished,
            this, &DeviceScannerService::onScanningFinished);
}

void DeviceScannerService::onScanningDeviceDiscovered(const QBluetoothDeviceInfo &info) {
    qDebug() << "Found device" << info.address();
    if (info.coreConfigurations() & QBluetoothDeviceInfo::LowEnergyCoreConfiguration) {
        qDebug() << "--------------- Add Device";
        QString address;
#ifdef Q_OS_MAC
        address = info.deviceUuid().toString();
#else
        address = info.address().toString();
#endif
        qDebug() << "" << "address: " << address;
        qDebug() << "" << "name: " << info.name();
        emit foundDevice(address, info.name(), true); //test
        addDeviceToQueue(info);
    }
}

void DeviceScannerService::onScanningFinished() {
    qDebug() << Q_FUNC_INFO;

    Q_D(DeviceScannerService);

    d->isScanning = false;

    emit scanningFinished();
}

void DeviceScannerService::addDeviceToQueue(const QBluetoothDeviceInfo &info) {
    Q_D(DeviceScannerService);
    qDebug() << Q_FUNC_INFO;
    if (!d->discoveredDevices.contains(info.address().toString())) {
        d->discoveredDevices.append(info.address().toString());
    }
}

void DeviceScannerService::timeout() {
    qDebug() << Q_FUNC_INFO;
}

void DeviceScannerService::startScanning() {
    Q_D(DeviceScannerService);

    if (d->isScanning) {
        return;
    }

    d->discoveryAgent->start();
    d->isScanning = true;
    emit scanningStarted();

    QTimer::singleShot(1000*1000, this, [this]() {
        this->stopScanning();
    });
}

void DeviceScannerService::onScanningDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error error) {
    Q_D(DeviceScannerService);

    if (error == QBluetoothDeviceDiscoveryAgent::PoweredOffError)
        qDebug()<<"The Bluetooth adaptor is powered off, power it on before doing discovery.";
    else if (error == QBluetoothDeviceDiscoveryAgent::InputOutputError)
         qDebug()<<"Writing or reading from the device resulted in an error.";
    else
        qDebug()<<"An unknown error has occurred.";

    d->isScanning = false;
    emit scanningFinished();
}

void DeviceScannerService::errorReceived(QLowEnergyController::Error /*error*/) {
    Q_D(DeviceScannerService);
    d->discoveryAgent->stop();

    d->isScanning = false;
    emit scanningFinished();
}

void DeviceScannerService::stopScanning() {
    Q_D(DeviceScannerService);

    qDebug() << "Forced stop scanning";

    if (!d->isScanning) {
        return;
    }
    d->discoveryAgent->stop();

    d->isScanning = false;
    emit scanningFinished();
}
