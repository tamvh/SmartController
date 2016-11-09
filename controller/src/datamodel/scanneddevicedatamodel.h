#ifndef SCANNEDDEVICEDATAMODEL_H
#define SCANNEDDEVICEDATAMODEL_H

#include "zabstractrowdatamodel.h"

class ScannedDeviceDataModel: public ZAbstractRowDataModel
{
public:
    ScannedDeviceDataModel(const QString &deviceAddress,
                           const QString &deviceName,
                           bool hasLampService);
    ~ScannedDeviceDataModel();
    enum {
        ScannedDeviceDataModelRoleAddress = Qt::UserRole + 6500,
        ScannedDeviceDataModelRoleName,
        ScannedDeviceDataModelRoleSelected,
        ScannedDeviceDataModelRoleHasLampService,
    };
public:
    static QHash<int, QByteArray> roleNames();
    virtual QString typeName() const override;
    virtual QVariant data(int role) const override;

    virtual bool setData(const QVariant& /*value*/, int /*role*/) override;
    virtual bool setItemData(const QMap<int, QVariant> &/*roles*/) override;
    virtual bool compare(const QVariant& /*value*/) const override;

private:
    QString address_;
    QString name_;
    bool selected_;
    bool hasLampService_;
};

#endif // SCANNEDDEVICEDATAMODEL_H
