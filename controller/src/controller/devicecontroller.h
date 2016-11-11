#ifndef DEVICECONTROLLER_H
#define DEVICECONTROLLER_H
#include <QDebug>
#include <QObject>
#include <QSharedPointer>
#include <QAbstractListModel>

class ZListDataModel;
class DeviceManager;
class DeviceController : public QObject
{
    Q_OBJECT
public:
    explicit DeviceController(QObject *parent = 0);
public slots:
    Q_INVOKABLE int controlDevice(int deviceId, const QString& remoteAddress, int action);
    Q_INVOKABLE int deleteDevice(int deviceId, const QString& remoteAddress);
    Q_INVOKABLE int addDevice(const QString& remoteAddress,
                              const QString& deviceName,
                              const QString& groupName,
                              int deviceType);
    Q_INVOKABLE bool checkDeviceExisted(const QString& deviceAddress);
    Q_INVOKABLE int controlDevice(const QString& remoteAddress, int value);
    QAbstractListModel* listDevice() const;
    QAbstractListModel* listDevice(const QString& groupName) const;
private:
    QByteArray m_postData;
    void addPostItem(const QString &key, const QString &value);
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // DEVICECONTROLLER_H
