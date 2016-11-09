#ifndef GROUPSERVICE_H
#define GROUPSERVICE_H
#include <QDebug>
#include <QObject>
#include <QString>

class GroupService : public QObject
{
    Q_OBJECT
public:
    explicit GroupService(QObject* parent = 0);
public slots:
    int deleteGroup(int32_t groupId);
    int addGroup(const QString& groupName,
                 const QString& groupAvatar,
                 const QString& groupType);
};

#endif // GROUPSERVICE_H
