#include "devicecalendardatamodel.h"

DeviceCalendarDataModel::DeviceCalendarDataModel(
        int32_t deviceId, int32_t calendarId,
        int32_t autoOn, int32_t repeat, int64_t eventTime) :
  deviceId_(deviceId),
  calendarId_(calendarId),
  autoOn_(autoOn),
  repeatMode_(repeat),
  eventTime_(eventTime)
{

}

DeviceCalendarDataModel::DeviceCalendarDataModel(int32_t deviceId,
                                                 int32_t calendarId,
                                                 bool autoOn,
                                                 int hour,
                                                 int minute,
                                                 ZDeviceCalendarItem::RepeartType repeartType,
                                                 int actionType,
                                                 QList<QString> repeartItems):
    deviceId_(deviceId),
    calendarId_(calendarId),
    autoOn_(autoOn),
    m_hour(hour),
    m_minute(minute),
    m_repeartType(repeartType),
    actionType_(actionType),
    m_repeartItems(repeartItems)
{



}

DeviceCalendarDataModel::~DeviceCalendarDataModel() {

}

QHash<int, QByteArray> DeviceCalendarDataModel::roleNames()
{
    QHash<int, QByteArray> roles;
    roles[DeviceCalendarDataModelRoleDeviceId] = "deviceId";
    roles[DeviceCalendarDataModelRoleCalendarId] = "calendarId";
    roles[DeviceCalendarDataModelRoleAutoOn] = "autoOn";
    roles[DeviceCalendarDataModelRoleHour] = "hour";
    roles[DeviceCalendarDataModelRoleMinute] = "minute";
    roles[DeviceCalendarDataModelRoleRepeatMode] = "repeatMode";
    roles[DeviceCalendarDataModelRoleEventTime] = "eventTime";
    roles[DeviceCalendarDataModelRoleTimeText] = "timeText";
    roles[DeviceCalendarDataModelRepeartText] = "repeartText";
    roles[DeviceCalendarDataModelActionType] = "actionType";
    roles[DeviceCalendarDataModelRoleStatusText] = "statusText";
    return roles;
}

QString DeviceCalendarDataModel::typeName() const {
    return "deviceCalendarItem";
}

QVariant DeviceCalendarDataModel::data(int role) const {
    switch (role) {
    case DeviceCalendarDataModelRoleHour:
        return m_hour;
    case DeviceCalendarDataModelRoleMinute:
        return m_minute;
    case DeviceCalendarDataModelRoleRepeatMode:
        return m_repeartType;
    case DeviceCalendarDataModelRoleDeviceId:
        return deviceId_;
    case DeviceCalendarDataModelRoleCalendarId:
        return calendarId_;
    case DeviceCalendarDataModelRoleAutoOn:
        return autoOn_;
    case DeviceCalendarDataModelRoleRepeat:
        return repeatMode_;
    case DeviceCalendarDataModelRoleEventTime:
        return eventTime_;
    case DeviceCalendarDataModelRoleTimeText: {
        QString timeText;
        QString type;
        QString hourStr;
        QString minuteStr;
        if (m_hour < 12) {
            type = "AM";
            hourStr = QString::number(m_hour);
        } else {
            type = "PM";
            hourStr = m_hour != 12?QString::number(m_hour - 12):QString::number(m_hour);
        }
        minuteStr = QString::number(m_minute);
        if (hourStr.length()<2) {
           hourStr = "0" + hourStr;
        }
        if (minuteStr.length()<2) {
           minuteStr = "0" + minuteStr;
        }
        timeText = hourStr + ":" + minuteStr + " " + type;
        return timeText;
    }
    case DeviceCalendarDataModelRepeartText: {
        switch (m_repeartType) {
        case ZDeviceCalendarItem::RepeartTypeEveryDay:
            return "Hàng ngày";
        case ZDeviceCalendarItem::RepeartTypeCustom: {
            QString string;
            for (int i = 0; i < m_repeartItems.size(); ++i) {
                string += m_repeartItems[i];
                if(i<m_repeartItems.size()-1)
                    string += ", " ;
            }
            return string;
        }
            return "Hàng ngày";
        case ZDeviceCalendarItem::RepeartTypeMonToFri:
            return "Từ thứ 2 - thứ 6";
        default:
            return "Một lần";
            break;
        }
    }
    case DeviceCalendarDataModelActionType:
        return actionType_;
    case DeviceCalendarDataModelRoleStatusText:
        return autoOn_?"Tự động bật":"Tự động tắt";
    default:
        return QVariant();
    }
}
