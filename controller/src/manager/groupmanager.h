#ifndef GROUPMANAGER_H
#define GROUPMANAGER_H
#include <QSharedPointer>
#include <vector>
#include <QObject>

class ZGroup;
class GroupManager : public QObject
{
    Q_OBJECT
public:
    GroupManager(QObject* parent = 0);
    ~GroupManager();
public:
    void initialize();
public:
    std::list<ZGroup>& getGroupList();
    ZGroup getGroup(const QString& groupName);
    ZGroup getGroup(int32_t groupId);
    int addGroup(ZGroup& group);
    void removeGroup(int32_t groupId, const QString& groupName);
    void updateGroup(const ZGroup& group);
signals:
    void groupListChanged();
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // GROUPMANAGER_H
