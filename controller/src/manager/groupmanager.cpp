#include <map>
#include <list>
#include <QDebug>
#include <src/model/zgroup.h>
#include "src/db/zgroupdb.h"
#include "groupmanager.h"

namespace {
    typedef std::map<int32_t, ZGroup> ZGroupMap;
    typedef ZGroupMap::iterator ZGroupMapIterator;
    typedef std::map<QString, ZGroup> ZGroupMapStr;
    typedef ZGroupMapStr::iterator ZGroupMapIteratorStr;
    typedef std::list<ZGroup> ZGroupList;
    typedef ZGroupList::iterator ZGroupListIterator;
    typedef std::map<QString, int32_t> ZGroupStateMap;
    typedef std::map<QString,int32_t>::iterator ZGroupStateMapIterator;
}

class GroupManager::Impl{
public:
    ZGroupMap groupCollection;
    ZGroupMapStr groupCollectionStr;
    ZGroupList groupList;
    ZGroupStateMap groupStateCollection;
    std::shared_ptr<ZGroupDB> _groupDB;
    Impl() {
        qDebug() << Q_FUNC_INFO;
        _groupDB = std::shared_ptr<ZGroupDB>(new ZGroupDB);
    }
};

GroupManager::GroupManager(QObject* parent)
    :QObject(parent),
    d_ptr(new Impl){
    qDebug() << Q_FUNC_INFO;    
}

GroupManager::~GroupManager() {
}

void GroupManager::initialize(){
    qDebug() << Q_FUNC_INFO;

    std::vector<QVariantMap> groupsVector = d_ptr->_groupDB.get()->getGroups();
    qDebug() << Q_FUNC_INFO << "groupsVector.size():" << groupsVector.size();
    if (groupsVector.size() <= 0) {
        return;
    }

    d_ptr->groupList.clear();
    d_ptr->groupCollection.clear();
    d_ptr->groupCollectionStr.clear();
    for (QVariantMap const& groupVariant: groupsVector) {
        int groupId = groupVariant["groupId"].toInt();
        QString groupName = groupVariant["groupName"].toString();
        QString groupAvatar = groupVariant["groupAvatar"].toString();
        int groupType = groupVariant["groupType"].toInt();
        qDebug() << Q_FUNC_INFO << "groupId:" << groupId;
        qDebug() << Q_FUNC_INFO << "groupName:" << groupName;
        qDebug() << Q_FUNC_INFO << "groupAvatar:" << groupAvatar;
        qDebug() << Q_FUNC_INFO << "groupType:" << QString::number(groupType);
        ZGroup group;
        group.setGroupId(static_cast<int32_t>(groupId));
        group.setGroupName(groupName);
        group.setGroupAvatar(groupAvatar);
        group.setGroupType(groupType);
        d_ptr->groupList.push_back(group);
        d_ptr->groupCollection[group.groupId()] = group;
        d_ptr->groupCollectionStr[group.groupName()] = group;
    }
}

std::list<ZGroup>& GroupManager::getGroupList() {
    return d_ptr->groupList;
}

ZGroup GroupManager::getGroup(const QString& groupName) {
    ZGroupMapIteratorStr itFind = d_ptr->groupCollectionStr.find(groupName);
    if (itFind == d_ptr->groupCollectionStr.end()) {
        return ZGroup();
    } else {
        return itFind->second;
    }
}

ZGroup GroupManager::getGroup(int32_t groupId) {
    ZGroupMapIterator itFind = d_ptr->groupCollection.find(groupId);
    if (itFind == d_ptr->groupCollection.end()) {
        return ZGroup();
    } else {
        return itFind->second;
    }
}

int GroupManager::addGroup(ZGroup& group) {
    // add group to db
    int result = d_ptr->_groupDB.get()->insertGroup(group);
    if (result <= 0) {
        //insertOrReplaceGroup fail
        qDebug() << Q_FUNC_INFO << "addGroup fail, result:" << result;
        return result;
    }
    // update new id
    group.setGroupId(result);
    const ZGroup& groupTmp = group;
    d_ptr->groupCollection.insert(std::pair<int32_t, ZGroup>(result, groupTmp));
    d_ptr->groupCollectionStr.insert(std::pair<QString, ZGroup>(group.groupName(), groupTmp));
    d_ptr->groupList.push_back(group);
    // signal new group added
    emit  groupListChanged();
    return group.groupId();
}

void GroupManager::removeGroup(int32_t groupId, const QString& groupName) {
    // remove from db
    bool result = d_ptr->_groupDB.get()->removeGroup(groupId);
    // signal group removed
    if (!result) {
        qDebug() << Q_FUNC_INFO << "removeGroup fail, result:" << result;
    }
    // remove from internal caching
    d_ptr->groupCollection.erase(groupId);
    d_ptr->groupList.remove(groupId);
    d_ptr->groupCollectionStr.erase(groupName);

    emit groupListChanged();
}





