#ifndef ZDEVICECALENDARITEM_H
#define ZDEVICECALENDARITEM_H

#include <QString>
#include <QList>

class ZDeviceCalendarItem
{
public:
    ZDeviceCalendarItem();
    typedef enum {
        RepeartTypeOnce = 0,
        RepeartTypeEveryDay,
        RepeartTypeMonToFri,
        RepeartTypeCustom
    } RepeartType;

    typedef enum {
        TurnOn = 0,
        TurnOff
    } ActionType;

void setHour(int hour) {
    hour_ = hour;
}
void setMinute(int minute) {
    minute_ = minute;
}

void setRepeartType(RepeartType repeartType) {
    repeartType_ = repeartType;
}

void setActionType(int actionType) {
    actionType_ = actionType;
}

void setRepeartItem(QList<QString> repeartItems) {
    repeartItems_ = repeartItems;
}

void setDeviceId(int32_t deviceId) {
    deviceId_ = deviceId;
}

void setCalendarId(int32_t calendarId) {
    calendarId_ = calendarId;
}

int deviceId() {
    return deviceId_;
}

int calendarId() {
    return calendarId_;
}

int hour() {
    return hour_;
}

int minute() {
    return minute_;
}

bool operator() (ZDeviceCalendarItem u) {
    if (u.calendarId() == calendarId())
        return true;
    return false;
}

RepeartType repeartType() {
    return repeartType_;
}

int actionType() {
    return actionType_;
}

QList<QString> repeartItems() {
    return repeartItems_;
}

public:
    //! associate event calendar with a device
    int32_t deviceId_;

    //! id of event
    int32_t calendarId_;

    //! auto-control mode:
    //! + autoOn_ == 0 -> device will be set OFF when timer is triggered
    //! + autoOn_ == 1 -> device will be set ON when timer is triggered
    int32_t autoOn_;

    //! timer repeat mode:
    //! + 0: Once
    //! + 1: Every day
    int32_t repeatMode_;

    //! Event time. Specify the time of day that timer will be triggered
    int64_t eventTime_;

    int hour_;
    int minute_;
    RepeartType repeartType_;
    int actionType_;
    QList<QString> repeartItems_;
};

#endif // ZDEVICECALENDARITEM_H
