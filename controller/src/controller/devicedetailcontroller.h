#ifndef DEVICEDETAILCONTROLLER_H
#define DEVICEDETAILCONTROLLER_H

#include <QObject>

class ZDevice;

class DeviceDetailController: public QObject
{
    Q_OBJECT
    Q_PROPERTY(int deviceId READ deviceId WRITE setDeviceId NOTIFY deviceInfoUpdated)
    Q_PROPERTY(QString remoteAddress READ remoteAddress WRITE setRemoteAddress NOTIFY deviceInfoUpdated)
    Q_PROPERTY(QString deviceName READ deviceName WRITE setDeviceName NOTIFY deviceInfoUpdated)
    Q_PROPERTY(QString deviceAvatar READ deviceAvatar WRITE setDeviceAvatar NOTIFY deviceInfoUpdated)
    Q_PROPERTY(bool deviceState READ deviceState NOTIFY deviceStateChanged)
public:
    explicit DeviceDetailController(QObject *parent = 0);

    Q_INVOKABLE void updateDeviceInfo(const int deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar);
    Q_INVOKABLE void updateDeviceTime(const int deviceId, const QString deviceAddress);
    Q_INVOKABLE void turnPlug(const QString deviceAddress, const bool isTurnOn);

signals:
    void deviceInfoUpdated();
    void deviceStateChanged();
    void updateDeviceTimeSuccess(const QString deviceAddress);
    void updateDeviceTimeFail(const QString deviceAddress);

public slots:
    void onUpdateDeviceTimeSuccess(const QString deviceAddress);
    void onUpdateDeviceTimeFail(const QString deviceAddress);

private:
    void initialize();

private :
    int32_t deviceId() const;
    QString remoteAddress() const;
    QString deviceName() const;
    QString deviceAvatar() const;
    bool deviceState() const;

    void setDeviceId(int value);
    void setRemoteAddress(const QString remoteAddress);
    void setDeviceName(const QString deviceName);
    void setDeviceAvatar(const QString deviceAvatar);

private:
    ZDevice* device;
    bool deviceState_;
};

#endif // DEVICEDETAILCONTROLLER_H
