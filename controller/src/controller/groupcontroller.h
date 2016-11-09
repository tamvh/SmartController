#ifndef GROUPCONTROLLER_H
#define GROUPCONTROLLER_H
#include <QDebug>
#include <QObject>
#include <QString>
#include <QAbstractListModel>
#include <QSharedPointer>

class ZListDataModel;
class GroupService;
class GroupManager;
enum enumGroupType{
    groupTypeNormal,
    groupTypeRoot,
};
class GroupController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QAbstractListModel* listGroup READ listGroup CONSTANT)
    Q_PROPERTY(std::list<QString> listGroupName READ listGroupName CONSTANT)
public:
    explicit GroupController(QObject *parent = 0);
public slots:

    Q_INVOKABLE int deleteGroup(int groupId, const QString& groupName);
    Q_INVOKABLE int addGroup(const QString& groupName);
    Q_INVOKABLE bool checkGroupExisted(const QString& groupName);
    QAbstractListModel* listGroup() const;
    std::list<QString> listGroupName() const;
private:
    void setRootRoom(int32_t groupId,
                        int32_t groupType,
                        const QString& groupName,
                        const QString& groupAvatar);

private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // GROUPCONTROLLER_H
