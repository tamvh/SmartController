#include "bluetoothservice.h"
#include "bluetoothcharacteristic.h"
#include <QLowEnergyController>
#include <QLowEnergyService>
#include <QBluetoothServiceInfo>

class BluetoothService::Private
{
public:
    Private(const QString &uuid, QLowEnergyService *service):
        _id(uuid),
        _service(service) {

    }

    BluetoothCharacteristic *characteristic(const QString &uuid) {
        Characteristics::iterator found = _characteristics.find(uuid);
        if (found == _characteristics.end())
            return NULL;
        return found.value();
    }

    BluetoothCharacteristic *createOrFind(const QString &uuid) {

        Characteristics::iterator found = _characteristics.find(uuid);
        if (found != _characteristics.end()) {
            qDebug() << "Characteristic existed: " << uuid;
            return found.value();
        }
        qDebug() << "Characteristic not existed: " << uuid;
        BluetoothCharacteristic *characteristic;
        characteristic = new BluetoothCharacteristic(uuid, NULL);
        _characteristics[uuid] = characteristic;
        return characteristic;
    }

    void discovery(QLowEnergyController &controler,
                   BluetoothService *service) {
        if (_service != NULL)
            delete _service;
        _service = controler.createServiceObject(QBluetoothUuid(_id));
        if (_service == NULL)
            return;
        QObject::connect(_service,
                         &QLowEnergyService::stateChanged,
                         [service](QLowEnergyService::ServiceState state) {
            if (state != QLowEnergyService::ServiceDiscovered)
                return;
            emit service->discovered(service);
        });

        QLowEnergyService::ServiceState state = _service->state();
        if (state == QLowEnergyService::DiscoveryRequired) {
            _service->discoverDetails();
            return;
        }

        if (state == QLowEnergyService::ServiceDiscovered)
            emit service->discovered(service);

    }

    inline QLowEnergyService *service() {
        return _service;
    }

    inline const QString &id() const {
        return _id;
    }

private:
    QString _id;
    QLowEnergyService *_service;
    typedef QMap<QString, BluetoothCharacteristic *> Characteristics;
    Characteristics _characteristics;


};

BluetoothService::BluetoothService(const QString &uuid,
                                   QLowEnergyService *service,
                                   QObject *parent):
    QObject(parent),
    d_ptr(new Private(uuid, service))

{

}

BluetoothCharacteristic *BluetoothService::characteristic(const QString &uuid)
{
    Q_D();
    return d->createOrFind(uuid);
}

QLowEnergyService *BluetoothService::service()
{
    Q_D();
    return d->service();
}

const QString &BluetoothService::id() const
{
    return d_ptr->id();
}

void BluetoothService::discovery(QLowEnergyController &controler)
{
    Q_D();
    d->discovery(controler, this);
}
