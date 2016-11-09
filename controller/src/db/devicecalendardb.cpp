#include <QDebug>
#include <QString>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

#include "devicecalendardb.h"
#include "db/updatabase.h"
#include "db/updatatable.h"
#include "src/app_commons.h"

#include "src/model/zdevicecalendaritem.h"

class DeviceCalendarDB::Private : public DB::UPDataTable {
private:
    typedef enum {
        TableSchema_Initial = 1,
        TableSchema_MonitorDeviceTableNameScheme = 2,
        TableSchema_ChangeTableNameScheme = 3,
        TableSchema_Current = TableSchema_ChangeTableNameScheme
    } TableSchema;
public:
    Private() : DB::UPDataTable(GlobalHandle::getApplicationDB())
    {
        qDebug()<<"______________________________Private() : DB::UPDataTable";
        m_tableName = "AlarmModelDB";
        qDebug()<<"verifyTableSchema";
        verifyTableSchema();
    }

    ~Private() {
    }
    QList<ZDeviceCalendarItem > getAllCalendarItemList()
    {
        QSqlQuery query(db());
        query.prepare(QString("SELECT calendarId, deviceId, autoOn, hour, minute, repeartType, actionType, repeartItems FROM %1").arg(m_tableName));
        QList<ZDeviceCalendarItem > result;
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return result;
        }
        while (query.next()) {
            ZDeviceCalendarItem calendarItem;
            calendarItem.calendarId_ = query.value("calendarId").toInt();
            calendarItem.deviceId_ = query.value("deviceId").toInt();
            calendarItem.autoOn_ = query.value("autoOn").toBool();
            calendarItem.hour_ = query.value("hour").toInt();
            calendarItem.minute_ = query.value("minute").toInt();
            calendarItem.repeartType_ = static_cast<ZDeviceCalendarItem::RepeartType>(query.value("repeartType").toInt());
            calendarItem.actionType_ = static_cast<int>(query.value("actionType").toInt());
            calendarItem.repeartItems_ = query.value("repeartItems").toString().split(",");
            result.append(calendarItem);
        }

        return result;
    }

    QList<ZDeviceCalendarItem > getCalendarItemList(int32_t deviceId)
    {
        qDebug()<< Q_FUNC_INFO;
        QSqlQuery query(db());
        query.prepare(QString("SELECT calendarId, deviceId, autoOn, hour, minute, repeartType, actionType, repeartItems FROM %1 WHERE deviceId = :deviceId ORDER BY hour, minute ASC").arg(m_tableName));
        query.bindValue(":deviceId", deviceId);
        QList<ZDeviceCalendarItem > result;
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return result;
        }
        while (query.next()) {
            ZDeviceCalendarItem calendarItem;
            calendarItem.calendarId_ = query.value("calendarId").toInt();
            calendarItem.deviceId_ = query.value("deviceId").toInt();
            calendarItem.autoOn_ = query.value("autoOn").toBool();
            calendarItem.hour_ = query.value("hour").toInt();
            calendarItem.minute_ = query.value("minute").toInt();
            calendarItem.repeartType_ = static_cast<ZDeviceCalendarItem::RepeartType>(query.value("repeartType").toInt());
            calendarItem.actionType_ = static_cast<int>(query.value("actionType").toInt());
            calendarItem.repeartItems_ = query.value("repeartItems").toString().split(",");
            result.append(calendarItem);
        }

        return result;
    }

    void addCalendarItem(ZDeviceCalendarItem calendarItem) {

    }

    void updateCalendarItem(ZDeviceCalendarItem calendarItem)
    {
        qDebug()<<"updateCalendarItem___1";
        bool result;
        QString repeartItemsString;
        for (int i = 0; i < calendarItem.repeartItems_.size(); ++i) {
            repeartItemsString += calendarItem.repeartItems_[i];
            if(i<calendarItem.repeartItems_.size()-1)
                repeartItemsString += "," ;
        }

        QSqlQuery query(database()->db());
        if (calendarItem.calendarId() == -1) {
            query.prepare(QString("INSERT OR REPLACE INTO %1(deviceId, autoOn, hour, minute, repeartType, actionType, repeartItems) VALUES (:deviceId, :autoOn, :hour, :minute, :repeartType, :actionType, :repeartItems)").arg(m_tableName));
        } else {
            query.prepare(QString("INSERT OR REPLACE INTO %1(calendarId, deviceId, autoOn, hour, minute, repeartType, actionType, repeartItems) VALUES (:calendarId,:deviceId, :autoOn, :hour, :minute, :repeartType, :actionType, :repeartItems)").arg(m_tableName));
            query.bindValue(":calendarId", calendarItem.calendarId_);
        }
        qDebug() << "-------------Device Calendar Info---------------";
        qDebug() <<":deviceId:  " + QString::number(calendarItem.deviceId_);
        qDebug() <<":autoOn: " + QString::number(calendarItem.autoOn_);
        qDebug() <<":hour: " + QString::number(calendarItem.hour_);
        qDebug() <<":minute: " + QString::number(calendarItem.minute_);
        qDebug() <<":repeartType: " + QString::number(calendarItem.repeartType_);
        qDebug() <<":actionType: " + QString::number(calendarItem.actionType_);
        qDebug() <<":repeartItems: " + repeartItemsString;
        qDebug() << "------------------------------------------------";

        query.bindValue(":deviceId", calendarItem.deviceId_);
        query.bindValue(":autoOn", calendarItem.autoOn_);
        query.bindValue(":hour", calendarItem.hour_);
        query.bindValue(":minute", calendarItem.minute_);
        query.bindValue(":repeartType", calendarItem.repeartType_);
        query.bindValue(":actionType", calendarItem.actionType_);
        query.bindValue(":repeartItems", repeartItemsString);
        result = query.exec();
        if(result){
            qDebug() << "add calendar success";
        }
        else
        {
            qDebug() << "add calendar faile";
        }
    }

    void insertCalendarItem(ZDeviceCalendarItem calendarItem)
    {
        qDebug()<<"insertCalendarItem";
        bool result;
        QString repeartItemsString;
        for (int i = 0; i < calendarItem.repeartItems_.size(); ++i) {
            repeartItemsString += calendarItem.repeartItems_[i];
            if(i<calendarItem.repeartItems_.size()-1)
                repeartItemsString += "," ;
        }

        QSqlQuery query(database()->db());
        query.prepare(QString("INSERT OR REPLACE INTO %1(deviceId, autoOn, hour, minute, repeartType, actionType, repeartItems) VALUES (:deviceId, :autoOn, :hour, :minute, :repeartType, :actionType, :repeartItems)").arg(m_tableName));
        qDebug() << "-------------Device Calendar Info---------------";
        qDebug() <<":deviceId:  " + QString::number(calendarItem.deviceId_);
        qDebug() <<":autoOn: " + QString::number(calendarItem.autoOn_);
        qDebug() <<":hour: " + QString::number(calendarItem.hour_);
        qDebug() <<":minute: " + QString::number(calendarItem.minute_);
        qDebug() <<":repeartType: " + QString::number(calendarItem.repeartType_);
        qDebug() <<":actionType: " + QString::number(calendarItem.actionType_);
        qDebug() <<":repeartItems: " + repeartItemsString;
        qDebug() << "------------------------------------------------";

        query.bindValue(":deviceId", calendarItem.deviceId_);
        query.bindValue(":autoOn", calendarItem.autoOn_);
        query.bindValue(":hour", calendarItem.hour_);
        query.bindValue(":minute", calendarItem.minute_);
        query.bindValue(":repeartType", calendarItem.repeartType_);
        query.bindValue(":actionType", calendarItem.actionType_);
        query.bindValue(":repeartItems", repeartItemsString);
        result = query.exec();
        if(result){
            qDebug() << "add calendar success";
        }
        else
        {
            qDebug() << "add calendar faile";
        }
    }

    void deleteCalendarItem(int calendarId) {
        QSqlQuery query(db());
        qDebug() << "calendarId: " + QString::number(calendarId);
        query.prepare(QString("DELETE FROM %1 WHERE calendarId = :calendarId").arg(m_tableName));
        query.bindValue(":calendarId", calendarId);
        if (!query.exec()) {
            qDebug() << "Execute SQL error: " << query.lastError();
            return;
        }
    }

protected:
    virtual QVariant tableSchemaVersionKey() const {
        return m_tableName;
    }
    virtual int tableSchemaVersionValue() const {
        return TableSchema_MonitorDeviceTableNameScheme;
    }
    virtual void createTableSchema() {
        qDebug()<<"createTableSchema DeviceInfo";
        QSqlQuery query(database()->db());
        query.exec("DROP TABLE IF EXISTS " + m_tableName);
        query.clear();


        QString querySql = QString("CREATE TABLE IF NOT EXISTS %1 ( "
                                   "  calendarId INTEGER PRIMARY KEY AUTOINCREMENT, "
                                   "  deviceId INTEGER, "
                                   "  autoOn BOOL, "
                                   "  hour INTEGER, "
                                   "  minute INTEGER, "
                                   "  repeartType INTEGER, "
                                   "  actionType INTEGER, "
                                   "  repeartItems STRING)")
                                  .arg(m_tableName);
        query.prepare(querySql);

        if (!query.exec() ) {
            qDebug() << "Execute SQL error: " << query.lastError();
        }
    }
private:
    QString m_tableName;
};
/*
    int index;
    int sourceHour;
    int sourceMinute;
    int hour;
    int minute;
*/
DeviceCalendarDB::DeviceCalendarDB():
    d_ptr(new Private())
{
//    qDebug()<<"______________________________DeviceCalendarDB_1_"<<d_ptr.get();
//    qDebug()<<"______________________________DeviceCalendarDB_2_"<<d_ptr.get();
}

DeviceCalendarDB::~DeviceCalendarDB()
{

}
QList<ZDeviceCalendarItem > DeviceCalendarDB::getAllCalendarItemList()
{
    return d_ptr->getAllCalendarItemList();
}

void DeviceCalendarDB::addCalendarItem(ZDeviceCalendarItem calendarItem) {
    qDebug()<<"addCalendarItem"<<this;
    d_ptr->addCalendarItem(calendarItem);
}

void DeviceCalendarDB::updateCalendarItem(ZDeviceCalendarItem calendarItem)
{
     qDebug()<<"updateCalendarItem"<<this;
    d_ptr->updateCalendarItem(calendarItem);
}

void DeviceCalendarDB::insertCalendarItem(ZDeviceCalendarItem calendarItem)
{
     qDebug()<<"insertCalendarItem"<<this;
    d_ptr->insertCalendarItem(calendarItem);
}

void DeviceCalendarDB::deleteCalendarItem(int calendarId)
{
    d_ptr->deleteCalendarItem(calendarId);
}

QList<ZDeviceCalendarItem >DeviceCalendarDB::getCalendarItemList() {
    qDebug()<< Q_FUNC_INFO;
    return d_ptr->getAllCalendarItemList();
}

QList<ZDeviceCalendarItem >DeviceCalendarDB::getCalendarItemList(int32_t deviceId) {
    qDebug()<< Q_FUNC_INFO;

    return d_ptr->getCalendarItemList(deviceId);
}


