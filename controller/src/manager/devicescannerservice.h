#ifndef DEVICESCANNERSERVICE_H
#define DEVICESCANNERSERVICE_H

#include <QObject>
#include <QSharedPointer>
#include <QLowEnergyController>
#include <QBluetoothServiceInfo>
#include <QBluetoothServiceDiscoveryAgent>

//! Provide a way for searching devices
class DeviceScannerService : public QObject
{
    Q_OBJECT
public:
    DeviceScannerService(QObject* parent=0);
signals:
    void foundDevice(const QString& remoteAddress, const QString& deviceName, bool hasLampService);
    void scanningStarted();
    void scanningFinished();
//    void updateDevice(const QString& remoteAddress, const QString& deviceName, bool hasLampService);
public slots:
    //! signals to be emitted are as follow:
    //! + scanningStarted
    //! + (zero or more) foundDevice
    //! + scanningFinished
    void startScanning();

    //! If scanning is in progress, will stop the scanning and emit signal scanningFinished
    void stopScanning();
private slots:
    void addDeviceToQueue(const QBluetoothDeviceInfo &info);
    void errorReceived(QLowEnergyController::Error);
    void timeout();

    void onScanningDeviceScanError(QBluetoothDeviceDiscoveryAgent::Error error);
    void onScanningDeviceDiscovered(const QBluetoothDeviceInfo &info);
    void onScanningFinished();
private:
    class DeviceScannerServicePrivate;
    QSharedPointer<DeviceScannerServicePrivate> d_ptr;

    Q_DECLARE_PRIVATE(DeviceScannerService)
};

#endif // DEVICESCANNERSERVICE_H
