#ifndef DEVICEDATAMODEL_H
#define DEVICEDATAMODEL_H
#include "zabstractrowdatamodel.h"


class DeviceDataModel: public ZAbstractRowDataModel
{
public:
    DeviceDataModel(int deviceId,
                    const QString &deviceName,
                    const QString &deviceIcon,
                    const QString &deviceValue,
                    const QString &sectionName);
    ~DeviceDataModel();
    enum {
        DeviceDataModelRoleName = Qt::UserRole + 6000,
        DeviceDataModelRoleIcon,
        DeviceDataModelRoleValue,
        DeviceDataModelRoleSection,
        DeviceDataModelRoleId
    };
public:
    static QHash<int, QByteArray> roleNames();
    virtual QString typeName() const override;
    virtual QVariant data(int role) const override;
private:
    QString m_name;
    QString m_icon;
    QString m_value;
    QString m_section;
    int m_id;
};

#endif // DEVICEDATAMODEL_H
