#ifndef DEVICELISTCONTROLLER_H
#define DEVICELISTCONTROLLER_H

#include <QObject>
class ZListDataModel;
class DeviceListController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(ZListDataModel *deviceModel READ deviceModel CONSTANT);
public:
    explicit DeviceListController(QObject *parent = 0);
    ~DeviceListController();
    ZListDataModel * deviceModel() {
        return m_deviceModel;
    }

signals:

public slots:
    void removeDeviceWithId(int deviceId);
    void addDevice(QString name,
                   QString icon,
                   QString value,
                   QString section);
    void editDevice(int id,
                    QString name,
                    QString icon,
                    QString value,
                    QString section);
private slots:
    void updateListContent();

private:
    ZListDataModel *m_deviceModel;
};

#endif // DEVICELISTCONTROLLER_H
