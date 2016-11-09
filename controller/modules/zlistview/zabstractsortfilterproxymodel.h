#ifndef SMARTTHINGS_ZABSTRACTSORTFILTERPROXYMODEL_H
#define SMARTTHINGS_ZABSTRACTSORTFILTERPROXYMODEL_H

#include <QObject>
#include <QSortFilterProxyModel>

class ZAbstractSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    enum FilterSyntax {
        RegExp,
        Wildcard,
        FixedString
    };

public:
    explicit ZAbstractSortFilterProxyModel(QObject *parent = 0);
    virtual ~ZAbstractSortFilterProxyModel();

public Q_SLOTS:
    QByteArray sortRole() const;
    void setSortRole(const QByteArray &role);

    void setSortOrder(Qt::SortOrder order);

    QByteArray filterRole() const;
    void setFilterRole(const QByteArray &role);

    QString filterString() const;
    void setFilterString(const QString &filter);

    void clearFilter();

    FilterSyntax filterSyntax() const;
    void setFilterSyntax(FilterSyntax syntax);

protected:
    QHash<int, QByteArray> roleNames() const;
    void performFilter();

protected:
    QByteArray m_sortRole;
    QByteArray m_filterRole;
};

#endif // SMARTTHINGS_ZABSTRACTSORTFILTERPROXYMODEL_H
