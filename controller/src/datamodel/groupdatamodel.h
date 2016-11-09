#ifndef GROUPDATAMODEL_H
#define GROUPDATAMODEL_H
#include <QString>
#include "zabstractrowdatamodel.h"

class GroupDataModel : public ZAbstractRowDataModel
{

public:
    GroupDataModel(int32_t id,
                   const QString& name,
                   const QString& avatar,
                   int32_t type,
                   int32_t totalDevice);
    ~GroupDataModel();
    enum {
        GroupModelRoleId = Qt::UserRole + 6600,
        GroupModelRoleName,
        GroupModelRoleAvatar,
        GroupModelRoleType,
        GroupModelRoleTotalDevice,
    };
public:
    static QHash<int, QByteArray> roleNames();
    virtual QString typeName() const override;
    virtual QVariant data(int role) const override;

    virtual bool setData(const QVariant& /*value*/, int /*role*/) override;
    virtual bool setItemData(const QMap<int, QVariant> &/*roles*/) override;
    virtual bool compare(const QVariant& /*value*/) const override;

private:
    int32_t _id;
    QString _name;
    QString _avatar;
    int32_t _type;
    int32_t _totalDevice;
};

#endif // GROUPDATAMODEL_H
