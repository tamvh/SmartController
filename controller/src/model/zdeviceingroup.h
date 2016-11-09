#ifndef ZDEVICEINGROUP_H
#define ZDEVICEINGROUP_H
#include <QObject>
#include <QDebug>
#include <QString>


class ZDeviceInGroup
{
public:
    ZDeviceInGroup();
    int32_t deviceId() const;
    void setDeviceId(int32_t value);
    int32_t deviceType() const;
    void setDeviceType(int32_t value);
    QString slave() const;
    void setSlave(const QString& value);
    QString deviceName() const;
    void setDeviceName(const QString& value);
    QString avatar() const;
    void setAvatar(const QString& value);
    int32_t groupId() const;
    void setGroupId(int32_t value);
    QString groupName() const;
    void setGroupName(const QString& value);
private:
    int32_t _deviceiId;
    int32_t _deviceType;
    QString _slave;
    QString _deviceName;
    QString _avatar;
    int32_t _groupId;
    QString _groupName;
};

#endif // ZDEVICEINGROUP_H
