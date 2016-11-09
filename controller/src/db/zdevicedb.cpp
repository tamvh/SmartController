#include "zdevicedb.h"
#include "db/updatabase.h"
#include "db/updatatable.h"
#include "src/model/zdevice.h"
#include "src/app_commons.h"
#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class ZDeviceDB::Private : public DB::UPDataTable {
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
        m_tableName = "ZDeviceDB";
        qDebug()<<"verifyTableSchema";
        verifyTableSchema();
    }

    ~Private() {
    }
    std::vector<QVariantMap> getDevices()
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT deviceId, remoteAddress, deviceName, groupName, deviceAvatar, deviceType FROM %1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return std::vector<QVariantMap>();
        }

        std::vector<QVariantMap> result;
        while (query.next()) {
            QVariantMap record;
            record["deviceId"] = query.value("deviceId");
            record["remoteAddress"] = query.value("remoteAddress");
            record["deviceName"] = query.value("deviceName");
            record["groupName"] = query.value("groupName");
            record["deviceAvatar"] = query.value("deviceAvatar");
            record["deviceType"] = query.value("deviceType");
            result.push_back(record);
        }
        return result;
    }

    std::vector<QVariantMap> getDevices(const QString& groupName)
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT deviceId, remoteAddress, deviceName, groupName, deviceAvatar, deviceType FROM %1 WHERE groupName == '%2'").arg(m_tableName).arg(groupName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return std::vector<QVariantMap>();
        }

        std::vector<QVariantMap> result;
        while (query.next()) {
            QVariantMap record;
            record["deviceId"] = query.value("deviceId");
            record["remoteAddress"] = query.value("remoteAddress");
            record["deviceName"] = query.value("deviceName");
            record["groupName"] = query.value("groupName");
            record["deviceAvatar"] = query.value("deviceAvatar");
            record["deviceType"] = query.value("deviceType");
            result.push_back(record);
        }
        return result;
    }

    ZDevice getLatestDevice() {
        QSqlQuery query(db());
        ZDevice device(-1);
        query.prepare(QString("SELECT deviceId, remoteAddress, deviceName, groupName, deviceAvatar, deviceType FROM %1 ORDER BY deviceId DESC LIMIT 1").arg(m_tableName));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return device;
        }

        while (query.next()) {
            device.setDeviceId(query.value("deviceId").toInt());
            device.setRemoteAddress(query.value("remoteAddress").toString());
            device.setDeviceName(query.value("deviceName").toString());
            device.setGroupName(query.value("groupName").toString());
            device.setDeviceAvatar(query.value("deviceAvatar").toString());
            device.setDeviceType(static_cast<ZDeviceType>(query.value("deviceType").toInt()));
            return device;
        }
        return device;
    }

    ZDevice getDevice(const QString deviceAddress) {
        QSqlQuery query(db());
        ZDevice device(-1);
        query.prepare(QString("SELECT deviceId, remoteAddress, deviceName, groupName, deviceAvatar, deviceType FROM %1 WHERE remoteAddress == '%2' ORDER BY deviceId DESC LIMIT 1").arg(m_tableName).arg(deviceAddress));
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return device;
        }

        while (query.next()) {
            device.setDeviceId(query.value("deviceId").toInt());
            device.setRemoteAddress(query.value("remoteAddress").toString());
            device.setDeviceName(query.value("deviceName").toString());
            device.setGroupName(query.value("groupName").toString());
            device.setDeviceAvatar(query.value("deviceAvatar").toString());
            device.setDeviceType(static_cast<ZDeviceType>(query.value("deviceType").toInt()));
            return device;
        }
        return device;
    }

    int insertDevice(ZDevice& device)
    {
        qDebug() << Q_FUNC_INFO << "deviceId:" << device.deviceId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(remoteAddress, deviceName, groupName, deviceAvatar, deviceType, groupName) VALUES (:remoteAddress, :deviceName, :groupName, :deviceAvatar, :deviceType, :groupName)").arg(m_tableName));
        const ZDevice deviceTemp= getDevice(device.remoteAddress());
        if (deviceTemp.deviceId() > 0) {
            return -1;
        }
        query.bindValue(":remoteAddress", device.remoteAddress());
        query.bindValue(":deviceName", device.deviceName());
        query.bindValue(":groupName", device.groupName());
        query.bindValue(":deviceAvatar", device.deviceAvatar());
        int deviceType = static_cast<int>(device.deviceType());
        qDebug() << "deviceType: " + QString::number(deviceType);
        query.bindValue(":deviceType", deviceType);
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        if (result) {
            if (device.deviceId() > 0) {
                return device.deviceId();
            } else {
                const ZDevice deviceTmp = getLatestDevice();
                qDebug() << Q_FUNC_INFO << "deviceTmp.deviceId:" << deviceTmp.deviceId();
                return deviceTmp.deviceId();
            }
        }
        return -1;
    }

    bool updateDevice(ZDevice& device)
    {
        qDebug() << Q_FUNC_INFO << "deviceId:" << device.deviceId();
        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(deviceId, remoteAddress, deviceName, groupName, deviceAvatar, deviceType) VALUES (:deviceId, :remoteAddress, :deviceName, :groupName, :deviceAvatar, :deviceType)").arg(m_tableName));
        query.bindValue(":deviceId", device.deviceId());
        query.bindValue(":remoteAddress", device.remoteAddress());
        query.bindValue(":deviceName", device.deviceName());
        query.bindValue(":groupName", device.groupName());
        query.bindValue(":deviceAvatar", device.deviceAvatar());
        int deviceType = static_cast<int>(device.deviceType());
        query.bindValue(":deviceType", deviceType);
        bool result = query.exec();
        qDebug() << Q_FUNC_INFO << "result:" << result;
        return result;
    }

    bool removeDevice(int32_t deviceId) {
        QSqlQuery query(database()->db());
        query.prepare(QString("DELETE FROM %1 WHERE deviceId = :deviceId").arg(m_tableName));
        query.bindValue(":deviceId", deviceId);
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
                                   "  deviceId INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "  remoteAddress TEXT NOT NULL, "
                                   "  deviceName TEXT, "
                                   "  deviceAvatar TEXT, "
                                   "  deviceType INTEGER, "
                                   "  groupName TEXT, "
                                   "  CONSTRAINT remoteAddress_unique UNIQUE (remoteAddress))")
                                  .arg(m_tableName);
        query.prepare(querySql);

        if (!query.exec() ) {
            qDebug() << Q_FUNC_INFO << "Execute SQL error: " << query.lastError();
        }
    }
private:
    QString m_tableName;
};

ZDeviceDB::ZDeviceDB():
    d_ptr(new Private())
{
    qDebug()<<"______________________________ZDeviceDB_1_"<<d_ptr.get();
}

ZDeviceDB::~ZDeviceDB()
{

}
std::vector<QVariantMap> ZDeviceDB::getDevices()
{
    return d_ptr->getDevices();
}

std::vector<QVariantMap> ZDeviceDB::getDevices(const QString& groupName) {
    return d_ptr->getDevices(groupName);
}

ZDevice ZDeviceDB::getLatestDevice() {
    return d_ptr->getLatestDevice();
}

ZDevice ZDeviceDB::getDevice(const QString deviceAddress) {
    return d_ptr->getDevice(deviceAddress);
}

int ZDeviceDB::insertDevice(ZDevice& device)
{
    return d_ptr->insertDevice(device);
}

bool ZDeviceDB::updateDevice(ZDevice& device)
{
    return d_ptr->updateDevice(device);
}

bool ZDeviceDB::removeDevice(int32_t deviceId)
{
    return d_ptr->removeDevice(deviceId);
}

