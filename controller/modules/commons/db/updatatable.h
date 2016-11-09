#ifndef SMARTTHINGS_UPDATATABLE_H
#define SMARTTHINGS_UPDATATABLE_H
#include <QString>
#include <QSqlDatabase>
#include <QVariant>

namespace DB {

class UPDatabase;
class UPDataTablePrivate;

class UPDataTable
{
public:
    UPDataTable(UPDatabase *db);
    UPDataTable(UPDataTablePrivate *ptr);

    virtual ~UPDataTable();
public:
    void verifyTableSchema();
protected:
    virtual void createTableSchema() = 0;
    virtual QVariant tableSchemaVersionKey() const = 0;
    virtual int tableSchemaVersionValue() const = 0;
protected:
    UPDatabase *database() const;
    QSqlDatabase db() const;
    void setDatabase(UPDatabase *db);
protected:
    UPDataTablePrivate *d_ptr;
    Q_DECLARE_PRIVATE(UPDataTable)
};

}
#endif // SMARTTHINGS_UPDATATABLE_H
