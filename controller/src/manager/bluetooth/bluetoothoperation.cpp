#include "bluetoothoperation.h"
#include "bluetoothservice.h"
#include "bluetoothcharacteristic.h"
#include <QLowEnergyService>
#include <QDebug>
#include <QMap>

class BluetoothOperation::Private
{
public:
    Private(const QString &service,
            const QString &characteristic):
        _service(service),
        _characteristic(characteristic) {

    }

    inline const QString &service() const {
        return _service;
    }

    inline const QString &characteristic() const {
        return _characteristic;
    }

    bool execute(BluetoothOperation *operation,
                 BluetoothWrite::Services &services) {
        BluetoothWrite::Services::iterator found = services.find(_service);
        if (found == services.end()) {
            qDebug() << "Service not found";
            return false;
        }

        BluetoothService *service = *found;
        BluetoothCharacteristic *characteristic;
        characteristic = service->characteristic(_characteristic);
        if (characteristic == NULL) {
            qDebug() << "Characteristic not found";
            return false;
        }

        return operation->execute(*characteristic, *service);
    }
private:
    QString _service;
    QString _characteristic;
};

BluetoothOperation::BluetoothOperation(const QString &service,
                                       const QString &characteristic,
                                       QObject *parent):
    QObject(parent),
    d_ptr(new Private(service, characteristic))
{

}

const QString &BluetoothOperation::service() const
{
    return d_ptr->service();
}

const QString &BluetoothOperation::characteristic() const
{
    return d_ptr->characteristic();
}

bool BluetoothOperation::execute(Services &services)
{
    Q_D();
    return d->execute(this, services);
}

/**
 * @brief BluetoothWrite::BluetoothWrite
 * @param service
 * @param characteristic
 * @param parent
 */
BluetoothWrite::BluetoothWrite(const QString &service,
                               const QString &characteristic,
                               const int &value,
                               QObject *parent):
    BluetoothOperation(service, characteristic, parent),
    _value(value)
{

}

bool BluetoothWrite::execute(BluetoothCharacteristic &characteristic,
                             BluetoothService &service)
{
    QObject::connect(service.service(),
                     &QLowEnergyService::characteristicWritten,
                     [this](const QLowEnergyCharacteristic &characteristic,
                     const QByteArray &value) {

        qDebug() << "Written";
        if (value.size() < sizeof(int))
            return;

        QString id = characteristic.uuid().toString();
        id.remove(0, 1);
        id.remove(id.length() - 1, 1);
        if (id != this->characteristic()) {
            qDebug() << "Characteristic wrong";
            return;
        }
        emit this->executed(this);
    });

    return characteristic.write(*service.service(), _value);
}

void BluetoothWrite::finish()
{
    emit written(service(), characteristic(), value());
}

/**
 * @brief BluetoothRead::BluetoothRead
 * @param service
 * @param characteristic
 * @param parent
 */
BluetoothRead::BluetoothRead(const QString &service,
                             const QString &characteristic,
                             QObject *parent):
    BluetoothOperation(service, characteristic, parent),
    _value(0)
{

}

bool BluetoothRead::execute(BluetoothCharacteristic &characteristic,
                            BluetoothService &service)
{
    return characteristic.read(*service.service());
}

void BluetoothRead::finish()
{
    emit readed(service(), characteristic(), _value);
}
