#include "updatatable.h"
#include "updatabase.h"
#include "updatatable_p.h"

namespace DB {

typedef enum {
    TableSchemaVersion_Initial = 1,
    TableSchemaVersion_Current = TableSchemaVersion_Initial
} TableSchemaVersion;


UPDataTable::UPDataTable(UPDatabase *db):
    d_ptr(new UPDataTablePrivate(db))
{

}

UPDataTable::~UPDataTable()
{
    if (d_ptr != nullptr) {
        delete d_ptr;
        d_ptr = nullptr;
    }
}

void UPDataTable::verifyTableSchema()
{
    Q_D(UPDataTable);
    Q_CHECK_PTR(d->database);
    int version = d->database->getValue(tableSchemaVersionKey()).toInt();
    if (version == tableSchemaVersionValue()) {
        return;
    }
    createTableSchema();
    d->database->setValue(tableSchemaVersionKey(), tableSchemaVersionValue());
}

void UPDataTable::setDatabase(UPDatabase *db)
{
    Q_D(UPDataTable);
    d->database = db;
}

UPDatabase *UPDataTable::database() const
{
    Q_D(const UPDataTable);
    return d->database;
}

QSqlDatabase UPDataTable::db() const
{
    Q_D(const UPDataTable);
    return d->database->db();
}

}
