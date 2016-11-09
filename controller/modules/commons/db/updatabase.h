#ifndef SMARTTHINGS_UPDATABASE_H
#define SMARTTHINGS_UPDATABASE_H

#include <QSqlDatabase>
#include <QVariant>

namespace DB {

enum class ConfigurationKey {
    Database = 1,
    GlobalConfig = 100,
    Favourites = 200,
    Cache = 300,
    Log = 400
};

class UPDatabasePrivate;
class UPDatabase
{
    enum {
        DatabaseVersion_Initial = 1,
        DatabaseVersion_ChangeConfigurationTable = 2,
        DatabaseVersion_Current = DatabaseVersion_ChangeConfigurationTable
    };
public:
    UPDatabase(const QString& databaseName);
    ~UPDatabase();
public:
    /// return false if cannot open database
    bool open();

    /// close database
    void close();
public:
    /// get value with key stored in Configurations table
    QVariant getValue(const QVariant &key);
    void setValue(const QVariant &key, const QVariant &value);
public:
    QSqlDatabase db() const;
private:
    UPDatabasePrivate* p;
};

}

#endif // SMARTTHINGS_UPDATABASE_H
