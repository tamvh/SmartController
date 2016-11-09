#include "devicehardwareservice.h"
#include "bluetooth/bluetoothservice.h"
#include "bluetooth/bluetoothoperation.h"
#include "bluetooth/bluetoothcontroller.h"
#include <QTimer>
#include <QDebug>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include "src/configuration.h"
#include <QTextCodec>

class DeviceHardwareService::DeviceHardwareServicePrivate {
public:
    /**
     * @brief DeviceHardwareServicePrivate
     * @param object
     */
    DeviceHardwareServicePrivate() :
        _controller(NULL),
        _initialized(false)
    {
    }
    ~DeviceHardwareServicePrivate()
    {

    }

    void connectToDevice(const QString &remoteAddress,
                         DeviceHardwareService *service)
    {
        if (_controller != NULL)
            return;
        qDebug() << "Initialize device info";

#ifdef Q_OS_MAC
        QBluetoothUuid uuid(remoteAddress);
        QBluetoothDeviceInfo info(uuid,"",0);
#else
        QBluetoothAddress address(remoteAddress);
        QBluetoothDeviceInfo info(address,"",0);
#endif
        qDebug() << "Create controller";
        _controller = new QLowEnergyController(info);
        QObject::connect(_controller,
                         &QLowEnergyController::connected,
                         [service]() {
            qDebug()<<"Connected";
            QLowEnergyController *controller = service->d_ptr->_controller;
            if (controller->state() == QLowEnergyController::DiscoveredState)
                return;

            qDebug()<<"Start discover";
            controller->discoverServices();
        });

        QObject::connect(_controller,
                         &QLowEnergyController::serviceDiscovered,
                         [service](const QBluetoothUuid &uuid) {
            QString id = uuid.toString();
            id.remove(0, 1);
            id.remove(id.length() - 1, 1);
            qDebug() << "Service discovered: "<< id;
            BluetoothService *bluetoothService;
            bluetoothService = service->d_ptr->createOrFind(id);
            service->d_ptr->_discoverings[bluetoothService] = bluetoothService;
        });

        QObject::connect(_controller,
                         &QLowEnergyController::discoveryFinished,
                         [service](){
            qDebug() << "Discovery finished";
            Discoverings &preparings = service->d_ptr->_discoverings;
            Discoverings::iterator iterator = preparings.begin();
            if (preparings.end() == iterator) {
                service->d_ptr->_initialized = true;
                return;
            }
            BluetoothService *bluetoothService = *iterator;
            bluetoothService->discovery(*service->d_ptr->controller());
        });


        QObject::connect(_controller, &QLowEnergyController::stateChanged,
                         [service](QLowEnergyController::ControllerState state){
            qDebug() << "State changed to: "<< state;
            if (QLowEnergyController::UnconnectedState == state) {
                qDebug() << "Reconnnect"<< state;
                service->d_ptr->_initialized = false;
                service->d_ptr->_controller->connectToDevice();
                return;
            }
        });

        qDebug() << "Connect to device";
        _address = remoteAddress;
        _controller->connectToDevice();
    }


    BluetoothService *createOrFind(const QString &uuid) {
        qDebug() << "Uuid: " << uuid;
        BluetoothWrite::Services::iterator found = _services.find(uuid);
        if (found != _services.end()) {
            qDebug() << "Service existed: " << uuid;
            return found.value();
        }

        qDebug() << "Service not existed: " << uuid;
        BluetoothService *service = new BluetoothService(uuid, NULL);
        _services[uuid] = service;
        QObject::connect(service,
                         &BluetoothService::discovered,
                         [this](BluetoothService *bluetooth) {
            qDebug() << "Service discovered: " << bluetooth->id();
            Discoverings::iterator iterator = _discoverings.find(bluetooth);
            if (iterator != _discoverings.end())
                _discoverings.erase(iterator);
            qDebug() << "Discoverings" << _discoverings.size();
            if (!_discoverings.empty()) {
                iterator = _discoverings.begin();
                BluetoothService *service = iterator.value();
                service->discovery(*_controller);
                return;
            }
            _initialized = true;
            qDebug() << "Initialized" << bluetooth->id();
            _writer.execute(&_services);
        });
        return service;
    }

    void write(DeviceHardwareService *service,
               const QString &serviceId,
               const QString &characteristicsId,
               const int value,
               QObject *parent = 0)
    {
        BluetoothWrite *write = new BluetoothWrite(serviceId,
                                                   characteristicsId,
                                                   value,
                                                   parent);
        QObject::connect(write,
                         &BluetoothWrite::written,
                         [service, write](QString serviceId,
                         QString characteristicsId,
                         int value) {

            if (serviceId != write->service() ||
                    characteristicsId != write->characteristic())
                return;

            const QString &address = service->d_ptr->_address;
            emit service->updateCharacteristicsSuccessful(address, value);
            service->d_ptr->_writer.execute(&service->d_ptr->_services);
        });
        _writer.schedule(write);
        if (!_initialized)
            return;
        _writer.execute(&_services);
    }


    inline QLowEnergyController *controller() {
        return _controller;
    }

    inline const QString &address() const {
        return _address;
    }


public:
    QLowEnergyController *_controller;
    BluetoothOperation::Services _services;
    typedef QMap<BluetoothService *, BluetoothService *> Discoverings;
    Discoverings _discoverings;
    BluetoothController _writer;
    bool _initialized;
    QString _address;

};

DeviceHardwareService::DeviceHardwareService(QObject *parent):
    QObject(parent),
    d_ptr(new DeviceHardwareServicePrivate)
{
}

void DeviceHardwareService::updateCharacteristic(const QString &remoteAddress,
                                                 const QString &service,
                                                 const QString &characteristics,
                                                 const int value)
{
    Q_D(DeviceHardwareService);
    d->connectToDevice(remoteAddress, this);
    d->write(this, service, characteristics, value);
}

void DeviceHardwareService::readValue(const QString &remoteAddress,
                                      const QString &service,
                                      const QString &characteristics)
{
    Q_D(DeviceHardwareService);
//    d->connectToDevice(remoteAddress, this);
//    d->read(this, service, characteristics, this);

}
