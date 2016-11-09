#ifndef SMARTTHINGS_ZABSTRACTROWDATAMODEL_H
#define SMARTTHINGS_ZABSTRACTROWDATAMODEL_H

#include <QVariant>

class ZAbstractRowDataModel
{
public:
    virtual ~ZAbstractRowDataModel() {}
//    static QHash<int, QByteArray> roleNames();
public:
    virtual QString typeName() const = 0;
    virtual QVariant data(int role) const = 0;
    virtual bool setData(const QVariant& /*value*/, int /*role*/) { return false; }
    virtual bool setItemData(const QMap<int, QVariant> &/*roles*/) { return false; }
    virtual bool compare(const QVariant& /*value*/) const { return false; }
};

#endif // SMARTTHINGS_ZABSTRACTROWDATAMODEL_H
