#ifndef SMARTTHINGS_UPDBGLOBALCONFIGURATIONSTABLE_H
#define SMARTTHINGS_UPDBGLOBALCONFIGURATIONSTABLE_H

#include "updatatable.h"
#include <QString>
#include <QVariant>

class UPDBGlobalConfigurationsTable : public DB::UPDataTable
{
public:
    UPDBGlobalConfigurationsTable(DB::UPDatabase *db);
    ~UPDBGlobalConfigurationsTable();
public:
    QVariant getValue(const QString &key, const QVariant &defaultValue);
    void setValue(const QString &key, const QVariant &value);
protected:
    virtual void createTableSchema();
    virtual QVariant tableSchemaVersionKey() const;
    virtual int tableSchemaVersionValue() const;
};

#endif // SMARTTHINGS_UPDBGLOBALCONFIGURATIONSTABLE_H
