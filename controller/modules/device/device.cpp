#include "device.h"
#include <QtQml>
#include "devicelistcontroller.h"
Device::Device()
{

}

Device::~Device()
{

}
void Device::registerTypes()
{
    qmlRegisterType<DeviceListController>("Device", 0, 1, "DeviceListController");
}

