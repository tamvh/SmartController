#ifndef BLUETOOTHCHARACTERISTIC_H
#define BLUETOOTHCHARACTERISTIC_H

#include <QObject>
#include <QSharedPointer>
class QLowEnergyService;
class BluetoothCharacteristic : public QObject
{
    Q_OBJECT
public:
    BluetoothCharacteristic(const QString &uuid,
                            QObject *parent = 0);
public:
    bool write(QLowEnergyService &service, int value);
    bool read(QLowEnergyService &service);
private:
    class Private;
    QSharedPointer<Private> d_ptr;
    Q_DECLARE_PRIVATE()
};

#endif // BLUETOOTHCHARACTERISTIC_H
