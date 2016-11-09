#ifndef BLUETOOTHSERVICE_H
#define BLUETOOTHSERVICE_H
#include <QObject>
#include <QSharedPointer>
class QLowEnergyController;
class QLowEnergyService;
class BluetoothCharacteristic;
class BluetoothService: public QObject
{
    Q_OBJECT
public:
    BluetoothService(const QString &uuid,
                     QLowEnergyService *service,
                     QObject *parent = 0);
public:
    BluetoothCharacteristic *characteristic(const QString &uuid);
    QLowEnergyService *service();
    const QString &id() const;
    void discovery(QLowEnergyController &controler);
signals:
    void discovered(BluetoothService *service);
private:
    class Private;
    QSharedPointer<Private> d_ptr;
    Q_DECLARE_PRIVATE()
};

#endif // BLUETOOTHSERVICE_H
