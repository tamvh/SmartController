#include <QDebug>

#include "devicelistcontroller.h"
#include "zlistdatamodel.h"
#include "datamodel/devicedatamodel.h"
#include "manager/devicemanager.h"
#include <QBluetoothLocalDevice>
DeviceListController::DeviceListController(QObject *parent) :
    QObject(parent),
    m_deviceModel(new ZListDataModel(parent))
{
    m_deviceModel->registerRoleNames(DeviceDataModel::roleNames());
    updateListContent();
    connect(DeviceManager::instance(),SIGNAL(deviceListChanged()),this, SLOT(updateListContent()));
}
void DeviceListController::updateListContent()
{
    DeviceManager *deviceManager = DeviceManager::instance();
    DeviceModelList devices = deviceManager->devices();
    QList<ZAbstractRowDataModelPtr> contents;
    foreach (DeviceModel deviceModel, devices) {
        contents.append(ZAbstractRowDataModelPtr(new DeviceDataModel(deviceModel.id,
                                                                     deviceModel.name,
                                                                     deviceModel.icon,
                                                                     deviceModel.value,
                                                                     deviceModel.section)));

    }
    m_deviceModel->setListContent(contents);
}

void DeviceListController::removeDeviceWithId(int deviceId)
{
    qDebug()<<"remove Device With Id" << deviceId;
    DeviceManager::instance()->removeDeviceWithId(deviceId);
}
void DeviceListController::addDevice(QString name,
                                     QString icon,
                                     QString value,
                                     QString section)
{
    DeviceManager::instance()->addDevice(name,icon,value,section);
}
void DeviceListController::editDevice(int id,
                                      QString name,
                                      QString icon,
                                      QString value,
                                      QString section)
{
    DeviceManager::instance()->editDevice(id,
                                          name,
                                          icon,
                                          value,
                                          section);
}

DeviceListController::~DeviceListController()
{
}

