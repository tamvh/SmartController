#include "db/updatabase.h"
#include "db/updatatable.h"
#include "src/model/zgroup.h"
#include "src/app_commons.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "zgroupdb.h"

class ZGroupDB::Private : public DB::UPDataTable {
private:
    typedef enum {
        TableSchema_Initial = 1,
        TableSchema_ZGroupTableNameScheme = 2,
        TableSchema_ChangeTableNameScheme = 3,
        TableSchema_Current = TableSchema_ChangeTableNameScheme
    } TableSchema;
public:
    Private() : DB::UPDataTable(GlobalHandle::getApplicationDB())
    {
        qDebug()<< Q_FUNC_INFO;
        m_tableName = "ZGroupDB";
        qDebug()<<"verifyTableSchema";
        verifyTableSchema();
    }

    ~Private() {
    }

    std::vector<QVariantMap> getGroups()
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT groupId, groupName, groupAvatar, groupType FROM %1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return std::vector<QVariantMap>();
        }
        std::vector<QVariantMap> result;
        while (query.next()) {
            QVariantMap record;
            record["groupId"] = query.value("groupId");
            record["groupName"] = query.value("groupName");
            record["groupAvatar"] = query.value("groupAvatar");
            record["groupType"] = query.value("groupType");
            result.push_back(record);
        }
        return result;
    }

    ZGroup getLatestGroup() {
        QSqlQuery query(db());
        ZGroup group(-1);
        query.prepare(QString("SELECT groupId, groupName, groupAvatar, groupType FROM %1 ORDER BY groupId DESC LIMIT 1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return group;
        }

        while (query.next()) {
            group.setGroupId(query.value("groupId").toInt());
            group.setGroupName(query.value("groupName").toString());
            group.setGroupAvatar(query.value("groupAvatar").toString());
            group.setGroupType(query.value("groupType").toInt());
            return group;
        }
        return group;
    }

    ZGroup getGroup(const QString& groupName) {
        QSqlQuery query(db());
        ZGroup group(-1);
        query.prepare(QString("SELECT groupId, groupName, groupAvatar, groupType FROM %1 WHERE groupName == '%2' ORDER BY deviceId DESC LIMIT 1").arg(m_tableName).arg(groupName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return group;
        }
        while (query.next()) {
            group.setGroupId(query.value("groupId").toInt());
            group.setGroupName(query.value("groupName").toString());
            group.setGroupAvatar(query.value("groupAvatar").toString());
            group.setGroupType(query.value("groupType").toInt());
            return group;
        }
        return group;
    }

    int insertGroup(ZGroup& group)
    {
        qDebug() << Q_FUNC_INFO << "groupId:" << group.groupId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(groupName, groupAvatar, groupType) VALUES (:groupName, :groupAvatar, :groupType)").arg(m_tableName));
        const ZGroup groupTemp= getGroup(group.groupName());
        if (groupTemp.groupId() > 0) {
            return -1;
        }
        query.bindValue(":groupName", group.groupName());
        query.bindValue(":groupAvatar", group.groupAvatar());
        query.bindValue(":groupType", static_cast<int>(group.groupType()));
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        if (result) {
            if (group.groupId() > 0) {
                return group.groupId();
            } else {
                const ZGroup groupTmp = getLatestGroup();
                int a = groupTmp.groupId();

                qDebug() << Q_FUNC_INFO << "groupTmp.groupId:" << groupTmp.groupId();
                return groupTmp.groupId();
            }
        }
        return -1;
    }

    bool updateGroup(ZGroup& group)
    {
        qDebug() << Q_FUNC_INFO << "groupId:" << group.groupId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(groupId, groupName, groupAvatar, groupType) VALUES (:groupId, :groupName, :groupAvatar, :groupType)").arg(m_tableName));
        query.bindValue(":groupId", group.groupId());
        query.bindValue(":groupName", group.groupName());
        query.bindValue(":groupAvatar", group.groupAvatar());
        query.bindValue(":groupType", static_cast<int>(group.groupType()));
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        return result;
    }

    bool removeGroup(int32_t groupId) {
        QSqlQuery query(database()->db());
        query.prepare(QString("DELETE FROM %1 WHERE groupId = :groupId").arg(m_tableName));
        query.bindValue(":groupId", static_cast<int>(groupId));

        return query.exec();
    }
protected:
    virtual QVariant tableSchemaVersionKey() const {
        return m_tableName;
    }
    virtual int tableSchemaVersionValue() const {
        return TableSchema_ZGroupTableNameScheme;
    }
    virtual void createTableSchema() {
        qDebug()<< Q_FUNC_INFO;
        QSqlQuery query(database()->db());
        query.exec("DROP TABLE IF EXISTS " + m_tableName);
        query.clear();

        QString querySql = QString("CREATE TABLE IF NOT EXISTS %1 ( "
                                   "  groupId INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "  groupName TEXT NOT NULL, "
                                   "  groupAvatar TEXT, "
                                   "  groupType INTEGER,"
                                   "  CONSTRAINT groupName_unique UNIQUE (groupName))")
                                  .arg(m_tableName);
        query.prepare(querySql);

        if (!query.exec() ) {
            qDebug() << Q_FUNC_INFO << "Execute SQL error: " << query.lastError();
        }
    }
private:
    QString m_tableName;
};


ZGroupDB::ZGroupDB() : d_ptr(new Private()) {
    qDebug()<<"______________________________ZGroupDB_1_"<<d_ptr.get();
}

ZGroupDB::~ZGroupDB(){
}

std::vector<QVariantMap> ZGroupDB::getGroups() {
    return d_ptr->getGroups();
}

ZGroup ZGroupDB::getGroup(const QString& groupName) {
    return d_ptr->getGroup(groupName);
}

ZGroup ZGroupDB::getLatestGroup(){
    return d_ptr->getLatestGroup();
}

int ZGroupDB::insertGroup(ZGroup& group) {
    return d_ptr->insertGroup(group);
}

bool ZGroupDB::updateGroup(ZGroup& group) {
    return d_ptr->updateGroup(group);
}

bool ZGroupDB::removeGroup(int32_t groupId) {
    return d_ptr->removeGroup(groupId);
}
