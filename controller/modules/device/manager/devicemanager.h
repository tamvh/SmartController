#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include <QObject>
#include <QSharedPointer>
#include "devicemodel.h"
class DeviceManager : public QObject
{
    Q_OBJECT
public:
    explicit DeviceManager(QObject *parent = 0);
    ~DeviceManager();
    DeviceModelList devices();
    static DeviceManager* instance();
signals:
    void deviceListChanged();
public slots:
    void removeDeviceWithId(int id);
    void addDevice(QString name,
                   QString icon,
                   QString value,
                   QString section);
    void editDevice(int id,
                    QString name,
                    QString icon,
                    QString value,
                    QString section);
private:
    class DeviceManagerPrivate;
    QSharedPointer<DeviceManagerPrivate> d_ptr;
    Q_DECLARE_PRIVATE(DeviceManager);
};

#endif // DEVICEMANAGER_H
