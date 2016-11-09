#ifndef UPSYSTEMSERVICE_H
#define UPSYSTEMSERVICE_H

#include <QObject>
#include <QObject>
#include <QVariantMap>
#include <QMetaType>

typedef bool (*MessageHandlerFunc)(QVariantMap data);

enum class UPServiceType {
    PresentLocalNotification,
    AlertView,
    DatePicker
};

Q_DECLARE_METATYPE(UPServiceType)

/// UPSystemService provides an interface for Qt/QML to access the platform-specific system service and function call.
class UPSystemService : public QObject
{
    Q_OBJECT
public:
    static UPSystemService* instance();
public:
    /// Send a message to the system
    Q_INVOKABLE bool sendMessage(UPServiceType serviceType, QVariantMap data);
public:
    void emitReceivedMessage(UPServiceType serviceType, QVariantMap data);
signals:
    /// The signal is emitted when a message is received.
    void received(UPServiceType serviceType, QVariantMap data);
private:
    explicit UPSystemService(QObject *parent = 0);
    void initializeMessageHandler();
    void registerMessageHandler(MessageHandlerFunc handler, UPServiceType serviceType);
    void unregisterMessageHandler(UPServiceType serviceType);
};

#endif // UPSYSTEMSERVICE_H
