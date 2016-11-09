#ifndef DEVICEMODEL
#define DEVICEMODEL
#include <QString>
#include <QList>
typedef struct DeviceModel
{
    int id;
    QString name;
    QString value;
    QString icon;
    QString section;

    bool operator == (int id_) {
        return id == id_;
    }
} DeviceModel;

inline bool operator == (const DeviceModel &u1, const DeviceModel &u2) {
    return u1.id == u2.id;
}

typedef QList<DeviceModel> DeviceModelList;
#endif // DEVICEMODEL

