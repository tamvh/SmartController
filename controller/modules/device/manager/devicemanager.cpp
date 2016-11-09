#include <algorithm>
#include "devicemanager.h"
#include "devicemodel.h"
#include <QCoreApplication>
class DeviceManager::DeviceManagerPrivate
{
public:
    DeviceManagerPrivate(DeviceManager &object)
        : q_ptr(&object)
    {

    }
    ~DeviceManagerPrivate() {}
    void getAllDevice() {
        deviceModelList.append(DeviceModel({0,"name","true","coffee-machine","A1"}));
        deviceModelList.append(DeviceModel({1,"name","false","coffee-machine","A1"}));
        deviceModelList.append(DeviceModel({2,"name","true","coffee-machine","A1"}));
        deviceModelList.append(DeviceModel({3,"name","false","coffee-machine","A2"}));
        deviceModelList.append(DeviceModel({4,"name","true","coffee-machine","A2"}));
        Q_Q(DeviceManager);
        q->deviceListChanged();
    }

public:
    DeviceModelList deviceModelList;
protected:
    DeviceManager * const q_ptr;
private:
    Q_DECLARE_PUBLIC(DeviceManager)
};

DeviceManager::DeviceManager(QObject *parent) :
    QObject(parent),
    d_ptr(new DeviceManagerPrivate(*this))
{
    Q_D(DeviceManager);
    d->getAllDevice();
}
DeviceManager *DeviceManager::instance()
{
    static DeviceManager * m_instance = 0;
    if (!m_instance) {
        QCoreApplication* app = QCoreApplication::instance();

        m_instance = new DeviceManager(app);
    }
    return m_instance;
}
void DeviceManager::removeDeviceWithId(int id)
{
    Q_D(DeviceManager);
    foreach (DeviceModel device, d->deviceModelList) {
        if (device.id == id) {
            d->deviceModelList.removeOne(device);
            deviceListChanged();
            return;
        }
    }
}
void DeviceManager::addDevice(QString name,
                              QString icon,
                              QString value,
                              QString section)
{
    Q_D(DeviceManager);
    int last = d->deviceModelList.last().id;
    d->deviceModelList.append(DeviceModel({last + 1,name,value,icon,section}));
    deviceListChanged();
}

void DeviceManager::editDevice(int id,
                               QString name,
                               QString icon,
                               QString value,
                               QString section)
{
    Q_D(DeviceManager);
    foreach (DeviceModel deviceModel, d->deviceModelList) {
        if (deviceModel.id == id) {
            d->deviceModelList.replace(d->deviceModelList.indexOf(deviceModel),
                                       DeviceModel({id,name,value,icon,section}));
            deviceListChanged();
            break;
        }
    }
}

DeviceManager::~DeviceManager()
{

}
DeviceModelList DeviceManager::devices()
{
    Q_D(DeviceManager);
    return d->deviceModelList;
}
