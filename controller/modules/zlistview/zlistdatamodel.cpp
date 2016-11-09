#include <QDebug>

#include "zlistdatamodel.h"
#include "zabstractrowdatamodel.h"

ZListDataModel::ZListDataModel(QObject *parent) :
    QAbstractListModel(parent),
    m_items()
{
    initialize();
}

void ZListDataModel::initialize()
{
    m_internalRoleNames[RowDataTypeRole] = "rowDataType";
}

void ZListDataModel::registerRoleNames(const QHash<int, QByteArray> &roleNames)
{
    m_internalRoleNames.unite(roleNames);
}

void ZListDataModel::addItem(ZAbstractRowDataModelPtr item)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    m_items.push_back(item);
    endInsertRows();
}

void ZListDataModel::insertItem(ZAbstractRowDataModelPtr item, const int pos)
{
    beginInsertRows(QModelIndex(), pos, pos);
    m_items.insert(pos, item);
    endInsertRows();
}

void ZListDataModel::replacedItem(ZAbstractRowDataModelPtr item, const int pos) {
    m_items[pos] = item;
    emit dataChanged(index(pos), index(pos));
}

void ZListDataModel::removeItem(const int position)
{
    beginRemoveRows(QModelIndex(), position, position);
    m_items.removeAt(position);
    endRemoveRows();
}

QModelIndex ZListDataModel::findItem(const QVariant &data)
{
    for (int loopIndex = 0; loopIndex < m_items.length(); loopIndex ++) {
        const ZAbstractRowDataModelPtr model = m_items.at(loopIndex);
        if (model->compare(data)) {
            return index(loopIndex);
        }
    }
    return QModelIndex();
}

void ZListDataModel::clear()
{
    beginResetModel();
    m_items.clear();
    endResetModel();
}

void ZListDataModel::setListContent(const QList<ZAbstractRowDataModelPtr>& contents)
{    
    beginResetModel();
    m_items = contents;
    endResetModel();
    emit listContentChanged();
}

const QList<ZAbstractRowDataModelPtr> &ZListDataModel::items() const
{
    return m_items;
}

int ZListDataModel::rowCount(const QModelIndex & parent) const
{
    Q_UNUSED(parent);
    return m_items.count();
}

QVariant ZListDataModel::data(const QModelIndex & index, int role) const
{
    if (index.row() < 0 || index.row() >= m_items.count()) {
        qDebug() << "Call data with invalid index";
        return QVariant();
    }

    ZAbstractRowDataModelPtr item = m_items.at(index.row());
    if (role == RowDataTypeRole) {
        return item->typeName();
    }

    if (role == RowDataItemRole) {
        return QVariant();
    }

    return item->data(role);
}

bool ZListDataModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.row() >= rowCount()) {
        return false;
    }

    if (role == RowDataTypeRole) {
        return false;
    }

    ZAbstractRowDataModelPtr item = m_items.at(index.row());
    bool retValue = item->setData(value, role);

    if (retValue) {
        emit dataChanged(index, index);
    }

    return retValue;
}

bool ZListDataModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if (index.row() >= rowCount()) {
        return false;
    }

    ZAbstractRowDataModelPtr item = m_items.at(index.row());
    bool retValue = item->setItemData(roles);

    if (retValue) {
        emit dataChanged(index, index);
    }

    return retValue;
}
