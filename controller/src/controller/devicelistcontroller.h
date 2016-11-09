#ifndef DEVICELISTCONTROLLER_H
#define DEVICELISTCONTROLLER_H

#include <QObject>
#include <QAbstractListModel>
#include <QTimer>
#include <QStack>
#include <QMutex>
#include <QQueue>
#include "src/model/zstackbright.h"
#include "src/model/zdevice.h"

class ZListDataModel;

class DeviceListController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* deviceList READ deviceList CONSTANT)
public:
    explicit DeviceListController(QObject *parent = 0);

signals:
//    void turnPlugSucess();
//    void turnPlugFail();
    void changeBrightSuccess();
    void changeBrightFail();
    void showMsg(const QString message);

    void startReadDevicesState();
    void readDeviceStateSuccess(const QString &remoteAddress, const QString &serviceUuid,const QString &characteristicsUuid,const QString &value);
    void readDeviceStateFail(const QString deviceAddress);
    void readDeviceStateFinish();
public slots:
    void changeBright(const QString deviceAddress, const int value);
//    void turnPlug(const QString deviceAddress, const bool isTurnOn);
    void onDeviceListChanged();
//    void onTurnPlugSuccess(const QString address, const bool isTurnOn);
//    void onTurnPlugFail(const QString address, const bool isTurnOn);
    void onChangeBrightSuccess(const QString deviceAddress, const int value);
    void onChangeBrightFail(const QString deviceAddress, const int value);

    void addToQueueReadDeviceState(const ZDevice device);
    void processReadDeviceState();
    void readDeviceState(const ZDevice *device);
    void readDevicesState();

    void onReadDeviceStateSuccess(const QString &remoteAddress, const QString &serviceUuid,const QString &characteristicsUuid,const QString &value);
    void onReadDeviceStateFail(const QString deviceAddress);

    void updateDeviceInfo(const int deviceId, const QString deviceAddress, const QString deviceName, const QString deviceAvatar);
    void addToStack(const QString deviceAddress, const int percentBright);
//    void processChangeBright();

private:
    static QByteArray deviceName() { return "GATT server"; }
    QAbstractListModel* deviceList() const;
    void initialize();
private:
    const int READ_DEVICE_STATE_TIMEOUT = 1000;
    ZListDataModel* deviceList_;
    QStack<ZQueueBright*> stackLampBright;
    QTimer *timeoutHelper;
    QMutex mutex;
    QQueue<ZDevice*> queueReadDeviceState;
    QTimer *timeoutReadDeviceState;
    int countRetry;
    QString currentDeviceAddress;
};

#endif // DEVICELISTCONTROLLER_H
