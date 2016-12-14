#include "db/updatabase.h"
#include "db/updatatable.h"
#include "src/model/zvalue.h"
#include "src/app_commons.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include "zcommondb.h"

class ZCommonDB::Private : public DB::UPDataTable {
private:
    typedef enum {
        TableSchema_Initial = 1,
        TableSchema_ZDeviceTableNameScheme = 2,
        TableSchema_ChangeTableNameScheme = 3,
        TableSchema_Current = TableSchema_ChangeTableNameScheme
    } TableSchema;
public:
    Private() : DB::UPDataTable(GlobalHandle::getApplicationDB())
    {
        qDebug()<< Q_FUNC_INFO;
        m_tableName = "ZCommonDB";
        qDebug()<<"verifyTableSchema";
        verifyTableSchema();
    }

    ~Private() {
    }

    std::vector<QVariantMap> getValues()
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT id, zkey, zvalue FROM %1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return std::vector<QVariantMap>();
        }

        std::vector<QVariantMap> result;
        while (query.next()) {
            QVariantMap record;
            record["id"] = query.value("id");
            record["zkey"] = query.value("zkey");
            record["zvalue"] = query.value("zvalue");
            result.push_back(record);
        }
        return result;
    }

    std::vector<QVariantMap> getValues(const QString& key)
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT id, zkey, zvalue FROM %1 WHERE zkey == '%2'").arg(m_tableName).arg(key));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return std::vector<QVariantMap>();
        }

        std::vector<QVariantMap> result;
        while (query.next()) {
            QVariantMap record;
            record["id"] = query.value("id");
            record["zkey"] = query.value("zkey");
            record["zvalue"] = query.value("zvalue");
            result.push_back(record);
        }
        return result;
    }

    ZValue getLatestValue() {
        QSqlQuery query(db());
        ZValue value(-1);
        query.prepare(QString("SELECT id, zkey, zvalue FROM %1 ORDER BY id DESC LIMIT 1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return value;
        }

        while (query.next()) {
            value.setId(query.value("id").toInt());
            value.setKey(query.value("zkey").toString());
            value.setValue(query.value("zvalue").toString());
            return value;
        }
        return value;
    }

    ZValue getValue(const QString key) {
        QSqlQuery query(db());
        ZValue value(-1);
        query.prepare(QString("SELECT id, zkey, zvalue FROM %1 WHERE zkey == '%2' ORDER BY id DESC LIMIT 1").arg(m_tableName).arg(key));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return value;
        }

        while (query.next()) {
            value.setId(query.value("id").toInt());
            value.setKey(query.value("zkey").toString());
            value.setValue(query.value("zvalue").toString());
            return value;
        }
        return value;
    }

    int insertValue(ZValue& value)
    {
        qDebug() << Q_FUNC_INFO << "id:" << value.getId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(zkey, zvalue) VALUES (:zkey, :zvalue)").arg(m_tableName));
        ZValue valueTemp= getValue(value.getKey());
        if (valueTemp.getId() > 0) {
            return -1;
        }
        query.bindValue(":zkey", value.getKey());
        query.bindValue(":zvalue", value.getValue());
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        if (result) {
            if (value.getId() > 0) {
                return value.getId();
            } else {
                ZValue valueTmp = getLatestValue();
                qDebug() << Q_FUNC_INFO << "valueTemp.getId:" << valueTmp.getId();
                return valueTmp.getId();
            }
        }
        return -1;
    }

    bool updateValue(ZValue& value)
    {
        qDebug() << Q_FUNC_INFO << "id:" << value.getId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(id, zkey, zvalue) VALUES (:id, :zkey, :zvalue)").arg(m_tableName));
        query.bindValue(":id", value.getId());
        query.bindValue(":zkey", value.getKey());
        query.bindValue(":zvalue", value.getValue());
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        return result;
    }

    bool removeValue(const QString& key) {
        QSqlQuery query(database()->db());
        query.prepare(QString("DELETE FROM %1 WHERE zkey = :zkey").arg(m_tableName));
        query.bindValue(":zkey", key);
        bool result = query.exec();
        if(!result) {
            qDebug() << "Execute SQL error: " << query.lastError();
        }
        return result;
    }
protected:
    virtual QVariant tableSchemaVersionKey() const {
        return m_tableName;
    }
    virtual int tableSchemaVersionValue() const {
        return TableSchema_ZDeviceTableNameScheme;
    }
    virtual void createTableSchema() {
        qDebug()<< Q_FUNC_INFO;
        QSqlQuery query(database()->db());
        query.exec("DROP TABLE IF EXISTS " + m_tableName);
        query.clear();

        QString querySql = QString("CREATE TABLE IF NOT EXISTS %1 ( "
                                   "  id INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "  zkey TEXT NOT NULL, "
                                   "  zvalue TEXT, "
                                   "  CONSTRAINT zkey_unique UNIQUE (zkey))")
                                  .arg(m_tableName);
        query.prepare(querySql);

        if (!query.exec() ) {
            qDebug() << Q_FUNC_INFO << "Execute SQL error: " << query.lastError();
        }
    }
private:
    QString m_tableName;
};

ZCommonDB::ZCommonDB() : d_ptr(new Private())
{
    qDebug()<<"______________________________ZCommonDB_1_" << d_ptr.get();
}

ZCommonDB::~ZCommonDB()
{
}

std::vector<QVariantMap> ZCommonDB::getValues() {
    return d_ptr->getValues();
}

std::vector<QVariantMap> ZCommonDB::getValues(const QString& key){
    return d_ptr->getValues(key);
}

ZValue ZCommonDB::getLatestValue() {
    return d_ptr->getLatestValue();
}

ZValue ZCommonDB::getValueItem(const QString& key) {
    return d_ptr->getValue(key);
}

int ZCommonDB::insertValue(ZValue& value) {
    return d_ptr->insertValue(value);
}

bool ZCommonDB::updateValue(ZValue& value) {
    return d_ptr->updateValue(value);
}

bool ZCommonDB::removeValue(const QString& key) {
    return d_ptr->removeValue(key);
}


