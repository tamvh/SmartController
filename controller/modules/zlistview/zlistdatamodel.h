#ifndef SMARTTHINGS_ZLISTDATAMODEL_H
#define SMARTTHINGS_ZLISTDATAMODEL_H

//#include "datamodel.h"

#include <QAbstractListModel>
#include <QSharedPointer>

class ZAbstractRowDataModel;
typedef QSharedPointer<ZAbstractRowDataModel> ZAbstractRowDataModelPtr;

class ZListDataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DefaultDataRoles {
        RowDataTypeRole = Qt::UserRole + 1000,
        RowDataItemRole,
    };

public:
    Q_ENUMS(DefaultDataRoles)
    explicit ZListDataModel(QObject *parent = 0);

public:
    void addItem(ZAbstractRowDataModelPtr item);
    void insertItem(ZAbstractRowDataModelPtr item, const int pos);
    void replacedItem(ZAbstractRowDataModelPtr item, const int pos);
    void removeItem(const int position);
    QModelIndex findItem(const QVariant &data);
    void clear();
    void registerRoleNames(const QHash<int, QByteArray> &roleNames);

    const QList<ZAbstractRowDataModelPtr> &items() const;

signals:
    void listContentChanged();
    
public:
    Q_INVOKABLE int rowCount(const QModelIndex & parent = QModelIndex()) const;
    Q_INVOKABLE QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    virtual bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles);
public slots:
    void setListContent(const QList<ZAbstractRowDataModelPtr>& contents);

protected:
    QHash<int, QByteArray> roleNames() const { return m_internalRoleNames; }

private:
    bool isTypeRegistered(ZAbstractRowDataModelPtr &item) const;
    void registerType(ZAbstractRowDataModelPtr &item);
    void initialize();

private:
    QList<ZAbstractRowDataModelPtr> m_items;
    QHash<int, QByteArray> m_internalRoleNames;
};

#endif // SMARTTHINGS_ZLISTDATAMODEL_H
