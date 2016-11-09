#include "bluetoothcharacteristic.h"
#include <QLowEnergyService>
#include <QBluetoothServiceInfo>


class BluetoothCharacteristic::Private
{
public:
    Private(const QString &uuid):
        _uuid(uuid) {

    }

public:

    bool read(QLowEnergyService &service) {
        QLowEnergyCharacteristic ch;
        ch = service.characteristic(QBluetoothUuid(_uuid));
        if (!ch.isValid())
            return false;
        qDebug() << "read";
        service.readCharacteristic(ch);
        return true;
    }

    bool write(QLowEnergyService &service, int value) {

        QLowEnergyCharacteristic ch;
        ch = service.characteristic(QBluetoothUuid(_uuid));
        if (!ch.isValid())
            return false;

        qDebug() << "Write value:" << value;
        QByteArray payload;
        payload.append((const char *)&value, sizeof(int));
        service.writeCharacteristic(ch, payload);
        return true;
    }

    int value(bool *ok) const {
        if (_value.isNull()) {
            *ok = false;
            return 0;
        }
        *ok = true;
        return *(_value.data());
    }


private:
    QString _uuid;
    QSharedPointer<int> _value;
};


/**
 * @brief BluetoothCharacteristic::BluetoothCharacteristic
 * @param uuid
 * @param service
 * @param parent
 */
BluetoothCharacteristic::BluetoothCharacteristic(const QString &uuid,
                                                 QObject *parent):
    QObject(parent),
    d_ptr(new Private(uuid))
{

}

bool BluetoothCharacteristic::write(QLowEnergyService &service, int value)
{
    Q_D();
    return d->write(service, value);
}

bool BluetoothCharacteristic::read(QLowEnergyService &service)
{
    Q_D();
    return d->read(service);
}

