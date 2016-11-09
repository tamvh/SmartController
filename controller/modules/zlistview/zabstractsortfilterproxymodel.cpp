#include "zabstractsortfilterproxymodel.h"

ZAbstractSortFilterProxyModel::ZAbstractSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel(parent)
{

}

ZAbstractSortFilterProxyModel::~ZAbstractSortFilterProxyModel()
{

}

QByteArray ZAbstractSortFilterProxyModel::sortRole() const
{
    return m_sortRole;
}

void ZAbstractSortFilterProxyModel::setSortRole(const QByteArray &role)
{
    if (m_sortRole == role)
        return;

    m_sortRole = role;
}

void ZAbstractSortFilterProxyModel::setSortOrder(Qt::SortOrder order)
{
    QSortFilterProxyModel::sort(0, order);
}

QByteArray ZAbstractSortFilterProxyModel::filterRole() const
{
    return m_filterRole;
}

void ZAbstractSortFilterProxyModel::setFilterRole(const QByteArray &role)
{
    if (m_filterRole == role)
        return;

    m_filterRole = role;
}

QString ZAbstractSortFilterProxyModel::filterString() const
{
    return filterRegExp().pattern();
}

void ZAbstractSortFilterProxyModel::setFilterString(const QString &filter)
{
    setFilterRegExp(QRegExp(filter, filterCaseSensitivity(), static_cast<QRegExp::PatternSyntax>(filterSyntax())));
}

void ZAbstractSortFilterProxyModel::clearFilter()
{
    setFilterString("");
    QRegExp regExp(filterString(), Qt::CaseInsensitive);
    setFilterRegExp(regExp);
    invalidateFilter();
}

ZAbstractSortFilterProxyModel::FilterSyntax ZAbstractSortFilterProxyModel::filterSyntax() const
{
    return static_cast<FilterSyntax>(filterRegExp().patternSyntax());
}

void ZAbstractSortFilterProxyModel::setFilterSyntax(ZAbstractSortFilterProxyModel::FilterSyntax syntax)
{
    setFilterRegExp(QRegExp(filterString(), filterCaseSensitivity(), static_cast<QRegExp::PatternSyntax>(syntax)));
}

QHash<int, QByteArray> ZAbstractSortFilterProxyModel::roleNames() const
{
    if (QAbstractItemModel *source = sourceModel())
        return source->roleNames();

    return QHash<int, QByteArray>();
}

void ZAbstractSortFilterProxyModel::performFilter()
{
    invalidateFilter();
}

