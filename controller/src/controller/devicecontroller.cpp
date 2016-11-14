#include <map>
#include <list>
#include <QDebug>
#include <QSharedPointer>
#include <QDateTime>
#include <QCoreApplication>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QString>

#include "zlistdatamodel.h"
#include "../configuration.h"
#include "src/app_commons.h"
#include "src/datamodel/devicedatamodel.h"
#include "src/model/zdevice.h"
#include "src/manager/devicemanager.h"
#include "src/manager/devicemanager.h"

#include <../commons/networks/core/httprequest.h>
#include <../commons/networks/core/networkrequest.h>
#include <../commons/networks/core/networkresponse.h>
#include <../commons/networks/core/networkmanager.h>
#include <../commons/networks/core/httpclient.h>


#include "devicecontroller.h"
using namespace Network::Core;
class DeviceController::Impl {
public:
    ZListDataModel* listDevice;
    DeviceManager* deviceManager;
    HttpClient* httpClient;
};

DeviceController::DeviceController(QObject *parent)
    : QObject(parent),
      d_ptr(new Impl)
{
    d_ptr->listDevice = new ZListDataModel(this);
    d_ptr->listDevice->registerRoleNames(DeviceDataModel::roleNames());
    d_ptr->deviceManager = GlobalHandle::deviceManager();
    d_ptr->deviceManager->initialize();
    d_ptr->httpClient = GlobalHandle::httpClient();
    d_ptr->httpClient->init(Configuration::hostServer, Configuration::portServer);
}
int DeviceController::addDevice(const QString& remoteAddress,
                                const QString& deviceName,
                                const QString& groupName,
                                int deviceType){
    qDebug() << "start ADD device";
    int value = 0; //voltage
    bool hasLampService = false;
    QString calendarSummary = "";
    if(d_ptr->deviceManager->getDevice(remoteAddress).deviceId() > 0)
    {
        qDebug() << "device [" +remoteAddress + "] is existed";
        return -1;
    }

    //init device infomation
    int32_t deviceId = -1;
    QString deviceAvatar = "qrc:/images/ic_lamp.png";
    if(deviceType == 1) {
        deviceAvatar = "qrc:/images/light_type_1.png";
    }
    else if(deviceType == 2) {
        deviceAvatar = "qrc:/images/light_type_2.png";
    }

    ZDevice itemDevice;
    itemDevice.setDeviceId(deviceId);
    itemDevice.setRemoteAddress(remoteAddress);
    itemDevice.setDeviceName(deviceName);
    itemDevice.setGroupName(groupName);
    itemDevice.setDeviceAvatar(deviceAvatar);
    itemDevice.setDeviceType(static_cast<ZDeviceType>(deviceType));
    int result =d_ptr->deviceManager->addDevice(itemDevice);
    deviceId = result;
    qDebug() << "result add device: " + QString::number(result);
    if(result > 0)
    {
        ZAbstractRowDataModelPtr device(new DeviceDataModel(deviceId,
                                                            deviceName,
                                                            remoteAddress,
                                                            deviceType,
                                                            value,
                                                            hasLampService,
                                                            deviceAvatar,
                                                            calendarSummary));
        d_ptr->listDevice->addItem(device);

    }
    return 0;
}

void DeviceController::addPostItem(const QString &key, const QString &value)
{
    if (!m_postData.isEmpty()) {
        m_postData.append(",");
    }

    m_postData.append(key);
    m_postData.append(":");
    m_postData.append(value);
}

int DeviceController::controlDevice(int deviceId, const QString& remoteAddress, int action) {
    qDebug() << "start DELETE device, deviceId: " + QString::number(deviceId) +
                ", remoteAddress: " + remoteAddress +
                ", action: " + QString::number(action);
    QString api = "control";

//    d_ptr->httpClient->setRequestMethod(HttpRequestMethod::POST);
    d_ptr->httpClient->addPostItem("\"address\"","\"11:22\"");
    d_ptr->httpClient->addPostItem("\"id\"","\"3\"");
    d_ptr->httpClient->addPostItem("\"control\"","\"1\"");
    d_ptr->httpClient->sendRequest(api);

//    addPostItem("\"address\"","\"11:22\"");
//    addPostItem("\"id\"","\"3\"");
//    addPostItem("\"control\"","\"1\"");
//    m_postData = "{" + m_postData + "}";
//    QLoggingCategory::setFilterRules("qt.network.ssl.warning=false");
//    QNetworkAccessManager * mgr = new QNetworkAccessManager();
//    QNetworkRequest *request = new QNetworkRequest();
//    request->setUrl(QUrl("http://192.168.1.42:9980/control"));
//    request->setHeader(QNetworkRequest::ContentTypeHeader, "some/type");
//    QNetworkReply *rep = mgr->post(*request, m_postData);
    return 0;
}

int DeviceController::deleteDevice(int deviceId, const QString& remoteAddress){
    qDebug() << "start DELETE device, deviceId: " + QString::number(deviceId) + ", remoteAddress: " + remoteAddress;
    std::list<ZDevice> devices = d_ptr->deviceManager->getDeviceList();
    int pos = -1;
    for (ZDevice& itemDevice : devices) {
        pos += 1;
        qDebug() << "itemDevice.deviceId(): " + QString::number(itemDevice.deviceId());
        if(itemDevice.deviceId() == deviceId) {
            d_ptr->listDevice->removeItem(pos);
            d_ptr->deviceManager->removeDevice(deviceId, remoteAddress);
        }
    }
    return 0;
}

bool DeviceController::checkDeviceExisted(const QString& deviceAddress) {
    ZDevice device = d_ptr->deviceManager->getDevice(deviceAddress);
    if(device.deviceId() > 0)
        return true;
    return false;
}

int DeviceController::controlDevice(const QString& remoteAddress, int value) {
    qDebug() << "Start control device, remoteAddress: " + remoteAddress + ", value: " + QString::number(value);
//    try {
        QAndroidJniObject::callStaticMethod<jint>("org/qtproject/lamp/BroadcastSend","onStopAdvertising","(I)I", value);
        QAndroidJniObject::callStaticMethod<jint>("org/qtproject/lamp/BroadcastSend","onStartAdvertising","(I)I", value);
//    } catch () {
//        qDebug() << "Exception";
//    }
    return 0;
}



QAbstractListModel* DeviceController::listDevice() const {
    return d_ptr->listDevice;
}

QAbstractListModel* DeviceController::listDevice(const QString& groupName) const {
    d_ptr->listDevice->clear();

    std::list<ZDevice> devices = d_ptr->deviceManager->getDeviceList();
    qDebug() << "total device: " + QString::number(devices.size());
    int32_t deviceId = -1;
    QString deviceName = "";
    QString deviceAddress = "";
    int deviceType = 0;
    int deviceValue = 0;
    QString deviceAvatar = "";
    bool hasLampService = false;
    QString calendarSummary = "";

    for (ZDevice& itemDevice : devices) {
        if(itemDevice.groupName().compare(groupName) == 0) {
            deviceName = itemDevice.deviceName();
            deviceId = itemDevice.deviceId();
            deviceAddress = itemDevice.remoteAddress();
            deviceAvatar = itemDevice.deviceAvatar();
            deviceType = static_cast<int>(itemDevice.deviceType());
            ZAbstractRowDataModelPtr device(new DeviceDataModel(deviceId,
                                                                deviceName,
                                                                deviceAddress,
                                                                deviceType,
                                                                deviceValue,
                                                                hasLampService,
                                                                deviceAvatar,
                                                                calendarSummary));
            d_ptr->listDevice->addItem(device);
        }
    }

    return d_ptr->listDevice;
}


