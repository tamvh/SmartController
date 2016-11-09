#include <QDebug>
#include <zlistdatamodel.h>

#include "src/app_commons.h"
#include "src/datamodel/devicecalendardatamodel.h"

#include "src/manager/devicemanager.h"
#include "src/manager/devicecalendarmanager.h"
#include "src/model/zdevice.h"
#include "src/model/zdevicecalendaritem.h"

#include "devicecalendarcontroller.h"

DeviceCalendarController::DeviceCalendarController(QObject *parent) : QObject(parent)
{
    calendarList_ = new ZListDataModel(this);
    calendarList_->registerRoleNames(DeviceCalendarDataModel::roleNames());
}

void DeviceCalendarController::removeCalendar(int calendarId) {
    DeviceCalendarManager* calendarManager = GlobalHandle::deviceCalendarManager();

    int pos = -1;
    ZDeviceCalendarList calendarItems = calendarManager->getCalendarItemList();
    for (ZDeviceCalendarItem& itemCalendar : calendarItems) {
        pos += 1;
        if(itemCalendar.calendarId() == calendarId)
        {
            calendarList_->removeItem(pos);
            calendarManager->removeDeviceCalendar(calendarId);
        }
    }
}

void DeviceCalendarController::updateCalendar() {

}

void DeviceCalendarController::addCalendar() {

}

int32_t DeviceCalendarController::deviceId() const {
    return deviceId_;
}

QString DeviceCalendarController::deviceName() const {
    return deviceName_;
}

QString DeviceCalendarController::deviceAvatar() const {
    return deviceAvatar_;
}

int32_t DeviceCalendarController::deviceState() const {
    return deviceState_;
}

void DeviceCalendarController::setDeviceId(int32_t value) {
    if (deviceId_ == value) {
        return;
    }

    // get device calendar
    deviceId_ = value;
    DeviceManager* manager = GlobalHandle::deviceManager();
    ZDevice d = manager->getDevice(deviceId_);
    deviceAvatar_ = d.deviceAvatar();
    deviceName_ = d.deviceName();
    deviceState_ = manager->getDeviceState(d.remoteAddress())?1:0;

    emit deviceInfoUpdated();

    initializeCalendarList();
}

//QAbstractListModel* DeviceCalendarController::calendarList() const {
//    qDebug() << "---------Start get list calendar---------";
//    DeviceCalendarManager* calendarManager = GlobalHandle::deviceCalendarManager();
//    ZDeviceCalendarList calendarItems = calendarManager->getCalendarItemList();
//    QList<ZAbstractRowDataModelPtr> contents;
//    for (ZDeviceCalendarItem& itemCalendar : calendarItems) {
//        DeviceCalendarDataModel *dataModel = new DeviceCalendarDataModel(itemCalendar.deviceId_,
//                                                                         itemCalendar.calendarId_,
//                                                                         itemCalendar.autoOn_,
//                                                                         itemCalendar.hour_,
//                                                                         itemCalendar.minute_,
//                                                                         itemCalendar.repeartType_,
//                                                                         itemCalendar.actionType_,
//                                                                         itemCalendar.repeartItems_
//                                                            );
//        contents.append(ZAbstractRowDataModelPtr(dataModel));
//    }
//    calendarList_->setListContent(contents);
//    qDebug() << "total calendar: " + QString::number(calendarList_->items().size());
//    return calendarList_;
//}

QAbstractListModel* DeviceCalendarController::calendarList(int deviceId) const {
    qDebug() << "Start get list calendar, deviceId: " + QString::number(deviceId);
    DeviceCalendarManager* calendarManager = GlobalHandle::deviceCalendarManager();
    ZDeviceCalendarList calendarItems = calendarManager->getCalendarItemList(deviceId);
    qDebug() << "TOTAL CALENDAR: " + QString::number(calendarItems.length()) + ", deviceId: " + QString::number(deviceId);
    calendarList_->clear();
    QList<ZAbstractRowDataModelPtr> contents;
    for (ZDeviceCalendarItem& itemCalendar : calendarItems) {
        DeviceCalendarDataModel *dataModel = new DeviceCalendarDataModel(itemCalendar.deviceId_,
                                                                         itemCalendar.calendarId_,
                                                                         itemCalendar.autoOn_,
                                                                         itemCalendar.hour_,
                                                                         itemCalendar.minute_,
                                                                         itemCalendar.repeartType_,
                                                                         itemCalendar.actionType_,
                                                                         itemCalendar.repeartItems_
                                                            );
        contents.append(ZAbstractRowDataModelPtr(dataModel));
    }
    calendarList_->setListContent(contents);
    qDebug() << "total calendar: " + QString::number(calendarList_->items().size());
    return calendarList_;
}

void DeviceCalendarController::initializeCalendarList() {
    DeviceCalendarManager* manager = GlobalHandle::deviceCalendarManager();
    ZDeviceCalendarList deviceCalendarItems = manager->getCalendarItemList(deviceId_);
    QList<ZAbstractRowDataModelPtr> contents;
    for (int i = 0; i < deviceCalendarItems.size(); ++i) {
        ZDeviceCalendarItem deviceCalendarItem = deviceCalendarItems.at(i);
        DeviceCalendarDataModel *dataModel = new DeviceCalendarDataModel(deviceCalendarItem.deviceId_,
                                                                         deviceCalendarItem.calendarId_,
                                                                         deviceCalendarItem.autoOn_,
                                                                         deviceCalendarItem.hour_,
                                                                         deviceCalendarItem.minute_,
                                                                         deviceCalendarItem.repeartType_,
                                                                         deviceCalendarItem.actionType_,
                                                                         deviceCalendarItem.repeartItems_
                                                            );
        contents.append(ZAbstractRowDataModelPtr(dataModel));
    }
    calendarList_->setListContent(contents);
}

void DeviceCalendarController::deleteDeviceCalendar(int row, int calendarId) {
    calendarList_->removeItem(row);
    DeviceCalendarManager* manager = GlobalHandle::deviceCalendarManager();
    manager->removeDeviceCalendar(calendarId);
}

void DeviceCalendarController::updateDeviceCalendar(int calendarId,
                                                    int deviceId,
                                                    int hour,
                                                    int minute,
                                                    int repeartMode,
                                                    int actionType,
                                                    QList<QString> repeartItems,
                                                    bool autoOn)
{
    qDebug()<<"______CPP_______";
    qDebug()<<"calendarId: " << calendarId;
    qDebug()<<"deviceId: " << deviceId;
    qDebug()<<"hour: " << hour;
    qDebug()<<"minute: "<< minute;
    qDebug()<<"repeartMode: " << repeartMode;
    qDebug()<<"actionType: " << actionType;
    qDebug()<<"Total repeat items: " << repeartItems.size();
    qDebug()<<"autoOn: "<<autoOn;

    ZDeviceCalendarItem calendarItem;
    calendarItem.setCalendarId(calendarId);
    calendarItem.setDeviceId(deviceId);
    calendarItem.setHour(hour);
    calendarItem.setMinute(minute);
    calendarItem.setRepeartType(static_cast<ZDeviceCalendarItem::RepeartType>(repeartMode));
    calendarItem.setActionType(static_cast<ZDeviceCalendarItem::ActionType>(actionType));
    calendarItem.setRepeartItem(repeartItems);
    calendarItem.autoOn_ = autoOn;
    DeviceCalendarManager* manager = GlobalHandle::deviceCalendarManager();
    manager->updateDeviceCalendar(deviceId, calendarItem);
    initializeCalendarList();
}

void DeviceCalendarController::insertDeviceCalendar(int deviceId,
                                                    int hour,
                                                    int minute,
                                                    int repeartMode,
                                                    int actionType,
                                                    QList<QString> repeartItems,
                                                    bool autoOn) {
    qDebug()<<"______CPP_______";
    qDebug()<<"deviceId: " << deviceId;
    qDebug()<<"hour: " << hour;
    qDebug()<<"minute: "<< minute;
    qDebug()<<"repeartMode: " << repeartMode;
    qDebug()<<"actionType: " << actionType;
    qDebug()<<"Total repeat items: " << repeartItems.size();
    qDebug()<<"autoOn: "<<autoOn;
    int calendarId = -1;
    ZDeviceCalendarItem calendarItem;
    calendarItem.setCalendarId(calendarId);
    calendarItem.setDeviceId(deviceId);
    calendarItem.setHour(hour);
    calendarItem.setMinute(minute);
    calendarItem.setRepeartType(static_cast<ZDeviceCalendarItem::RepeartType>(repeartMode));
    calendarItem.setActionType(static_cast<ZDeviceCalendarItem::ActionType>(actionType));
    calendarItem.setRepeartItem(repeartItems);
    calendarItem.autoOn_ = autoOn;
    DeviceCalendarManager* manager = GlobalHandle::deviceCalendarManager();
    manager->insertDeviceCalendar(deviceId, calendarItem);
    initializeCalendarList();
}
