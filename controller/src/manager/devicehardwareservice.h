#ifndef DEVICEHARDWARESERVICE_H
#define DEVICEHARDWARESERVICE_H
#include <QObject>
#include <QSharedPointer>
#include <functional>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>
#include <QTimer>

class DeviceHardwareService : public QObject
{
    Q_OBJECT
public:
    DeviceHardwareService(QObject *parent = 0);
    void updateCharacteristic(const QString &remoteAddress,
                          const QString &service,
                          const QString &characteristics,
                          const int value);
    void readValue(const QString &remoteAddress,
                   const QString &serviceUuid,
                   const QString &characteristicsUuid);

signals:
    void updateCharacteristicsSuccessful(const QString &remoteAddress, const int value);
    void updateCharacteristicsFailed(const QString &remoteAddress, const int value);

    void readCharacteristicsSuccessful(const QString &remoteAddress);
    void readCharacteristicsFailed(const QString &remoteAddress);

    void result(QString &remoteAddress,
                QString &serviceUuid,
                QString &characteristicsUuid,
                QString &value);

private:
    class DeviceHardwareServicePrivate;
    QSharedPointer<DeviceHardwareServicePrivate> d_ptr;
    Q_DECLARE_PRIVATE(DeviceHardwareService)

};

#endif // DEVICEHARDWARESERVICE_H
