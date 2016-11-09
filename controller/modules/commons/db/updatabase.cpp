#include <QtSql>
#include <QStandardPaths>
#include <QDir>
#include <QDebug>

#include "updatabase.h"

namespace DB {
QString pathAppend(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}

QString databaseFullPath(const QString &databaseName) {
    QString path = QStandardPaths::standardLocations(QStandardPaths::CacheLocation)[0];
    QString rootFolder = pathAppend(path, "Local");
    QDir dir(rootFolder);
    if (!dir.exists()) {
        dir.mkpath(rootFolder);
    }

    QString pathName = pathAppend(rootFolder, databaseName + ".sqlite");
    return pathName;
}

class UPDatabasePrivate
{
public:
    UPDatabasePrivate(const QString& databaseName):
        databasePath(databaseFullPath(databaseName))
    {
        db = QSqlDatabase::addDatabase("QSQLITE", databaseName);
        db.setDatabaseName(databasePath);
    }
    ~UPDatabasePrivate()
    {
        db.close();
    }
public:
    bool dropConfigurationTable() {
        QSqlQuery query(db);
        query.prepare("DROP TABLE IF EXISTS Configurations");
        return query.exec();
    }

    bool createConfigurationTable() {
        QSqlQuery query(db);
        query.prepare("CREATE TABLE IF NOT EXISTS Configurations ( \
                      key TEXT PRIMARY KEY, \
                      value INTEGER \
                          );");
        return query.exec();
    }

public:
    QString databasePath;
    QSqlDatabase db;
};

UPDatabase::UPDatabase(const QString& dbPath):
    p(new UPDatabasePrivate(dbPath))
{
}

UPDatabase::~UPDatabase()
{
    delete p;
}

void UPDatabase::close()
{
    p->db.close();
}

bool UPDatabase::open()
{
    if (p->db.isOpen()) {
        return true;
    }

    if (!p->db.open()) {
        return false;
    }

    int currentVersion = getValue((int)ConfigurationKey::Database).toInt();
    if (currentVersion != DatabaseVersion_Current) {
        p->dropConfigurationTable();
        p->createConfigurationTable();
        setValue((int)ConfigurationKey::Database, DatabaseVersion_Current);
    }
    return true;
}

QVariant UPDatabase::getValue(const QVariant &key)
{
    QSqlQuery query(p->db);
    query.prepare("SELECT value FROM Configurations WHERE key=:key");
    query.bindValue(":key", key);
    if (!query.exec()) {
        return false;
    }

    if (!query.next()) {
        return false;
    }

    return query.value("value");
}

void UPDatabase::setValue(const QVariant &key, const QVariant &value)
{
    QSqlQuery query(p->db);
    query.prepare("INSERT OR REPLACE INTO Configurations(key, value) VALUES (:key, :value)");
    query.bindValue(":key", key);
    query.bindValue(":value", value);
    query.exec();
}

QSqlDatabase UPDatabase::db() const
{
    return p->db;
}

}
