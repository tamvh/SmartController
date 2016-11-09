#include <QCoreApplication>
#include <QDebug>
#include "upsystemservice.h"

static QMap<UPServiceType, MessageHandlerFunc> handlers;
static UPSystemService * m_instance = 0;


UPSystemService *UPSystemService::instance()
{
    if (!m_instance) {
        QCoreApplication* app = QCoreApplication::instance();
        m_instance = new UPSystemService(app);
    }
    return m_instance;
}

UPSystemService::UPSystemService(QObject *parent) :
    QObject(parent)
{
    initializeMessageHandler();
}

bool UPSystemService::sendMessage(UPServiceType serviceType, QVariantMap data) {
    if (!handlers.contains(serviceType)) {
        return false;
    }

    return handlers[serviceType](data);
}

void UPSystemService::emitReceivedMessage(UPServiceType serviceType, QVariantMap data)
{
    emit received(serviceType, data);
}

void UPSystemService::registerMessageHandler(MessageHandlerFunc handler, UPServiceType serviceType)
{
    handlers[serviceType] = handler;
}

void UPSystemService::unregisterMessageHandler(UPServiceType serviceType)
{
    handlers.remove(serviceType);
}

#if !defined(Q_OS_IOS) && !defined(Q_OS_MAC) && !defined(Q_OS_ANDROID)
void UPSystemService::initializeMessageHandler()
{

}
#endif

