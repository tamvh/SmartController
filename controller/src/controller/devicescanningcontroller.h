#ifndef DEVICESCANNINGCONTROLLER_H
#define DEVICESCANNINGCONTROLLER_H

#include <QObject>
#include <QAbstractListModel>

class ZListDataModel;
class DeviceScannerService;

class DeviceScanningController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int scanningState READ scanningState NOTIFY scanningStateChanged)
    Q_PROPERTY(QAbstractListModel* deviceList READ deviceList CONSTANT)
public:
    explicit DeviceScanningController(QObject *parent = 0);

signals:
    void scanningStateChanged();
public slots:
    //! Start scanning for devices:
    //! + scanningState will be changed to 1
    //! + deviceList's content is reset
    //!
    //! When found a device, it will be added to deviceList
    //! When finished scanning, scanningState will be changed to 0
    Q_INVOKABLE void startScanDevices();
    Q_INVOKABLE void stopScanDevices();

//    //! Set a device to be added
    Q_INVOKABLE void selectDevice(const QString& remoteAddress);


//    //! Set a added device for exclusion
//    void unselectDevice(const QString& remoteAddress);

private slots:
    void onScanningStarted();
    void onScanningFinished();
    void onFoundDevice(const QString& remoteAddress, const QString& deviceName, bool hasLampService);
private:
    int scanningState() const;


    QAbstractListModel* deviceList() const;
private:
    int scanningState_;//scaning: 1
    ZListDataModel* deviceList_;
    DeviceScannerService* scannerService_;

};

#endif // DEVICESCANNINGCONTROLLER_H
