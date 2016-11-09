#include <QSql>
#include <QSqlQuery>
#include <QDebug>

#include "updbglobalconfigurationstable.h"
#include "updatabase.h"
#include "updatatable_p.h"


using namespace DB;
namespace {

typedef enum {
    TableSchema_Initial = 1,
    TableSchema_AddGlobalConfiguration,
    TableSchema_FixPrimaryKey,
    TableSchema_Current = TableSchema_FixPrimaryKey
} TableSchema;

}
UPDBGlobalConfigurationsTable::UPDBGlobalConfigurationsTable(UPDatabase *db):
    UPDataTable(db)
{
    verifyTableSchema();
}

UPDBGlobalConfigurationsTable::~UPDBGlobalConfigurationsTable()
{
}

QVariant UPDBGlobalConfigurationsTable::tableSchemaVersionKey() const
{
    return "globalConfig";
}

int UPDBGlobalConfigurationsTable::tableSchemaVersionValue() const
{
    return TableSchema_Current;
}

QVariant UPDBGlobalConfigurationsTable::getValue(const QString &key, const QVariant &defaultValue)
{
    Q_D(UPDataTable);
    QSqlQuery query(d->database->db());
    query.prepare("SELECT value FROM GlobalConfigurations WHERE key=:key");
    query.bindValue(":key", key);
    if (!query.exec()) {
        return defaultValue;
    }

    if (!query.next()) {
        return defaultValue;
    }

    return query.value("value");
}

void UPDBGlobalConfigurationsTable::setValue(const QString &key, const QVariant &value)
{
    qDebug() << "setValue to database";
    Q_D(UPDataTable);
    QSqlQuery query(d->database->db());
    query.prepare("INSERT OR REPLACE INTO GlobalConfigurations(key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

void UPDBGlobalConfigurationsTable::createTableSchema()
{
    Q_D(UPDataTable);
    QSqlQuery query(d->database->db());
    query.exec("DROP TABLE IF EXISTS GlobalConfigurations");
    query.clear();

    query.prepare(
         "CREATE TABLE IF NOT EXISTS GlobalConfigurations ( "
         "  key TEXT PRIMARY KEY, "
         "  value TEXT)");

    query.exec();
}

