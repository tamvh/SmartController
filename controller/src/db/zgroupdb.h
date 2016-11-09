#ifndef ZGROUPDB_H
#define ZGROUPDB_H
#include <QObject>
#include <memory>

class ZGroup;
class ZGroupDB
{
public:
    ZGroupDB();
    ~ZGroupDB();
public:
    std::vector<QVariantMap> getGroups();
    ZGroup getGroup(const QString& groupName);
    ZGroup getLatestGroup();
    int insertGroup(ZGroup& group);
    bool updateGroup(ZGroup& group);
    bool removeGroup(int32_t groupId);
private:
    class Private;
    std::shared_ptr<Private> d_ptr;
};

#endif // ZGROUPDB_H
