#ifndef BLUETOOTHGATT_H
#define BLUETOOTHGATT_H

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


class BluetoothAdvertising
{
public:
    BluetoothAdvertising();
    virtual ~BluetoothAdvertising();
    void addService(const QLowEnergyServiceData &serviceData);
    void addRunningSpeedService();
    void addGenericAccessService();
    void addCustomService();
    void startAdvertising();
    int advertisingPayload(const int value);
public:
    static QByteArray deviceName() { return "GATT server"; }
    static QScopedPointer<QLowEnergyController> leController;
    typedef QSharedPointer<QLowEnergyService> ServicePtr;
    static QHash<QBluetoothUuid, ServicePtr> services;
    static int descriptorWriteCount;
    static int disconnectCount;
    static QBluetoothAddress remoteDevice;
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // BLUETOOTHGATT_H
