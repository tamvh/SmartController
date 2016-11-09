#include <map>
#include <list>
#include <QDebug>
#include <QSharedPointer>
#include <QDateTime>
#include "src/app_commons.h"
#include "src/datamodel/groupdatamodel.h"
#include "src/model/zgroup.h"
#include "src/manager/groupservice.h"
#include "src/manager/devicemanager.h"
#include <src/manager/groupmanager.h>
//#include "QZXing.h"
#include "zlistdatamodel.h"
#include "groupcontroller.h"

class GroupController::Impl {
public:
//    QZXing* qZXing;
    ZListDataModel* listGroup;
    std::list<QString> listGroupName;
    GroupService* groupService;
    GroupManager* groupManager;
    DeviceManager* deviceManager;
    std::list<QString> listRootRoomTitle = {"livingroom", "bedroom", "bathroom", "other room"};
    std::map<QString, QString> listRootRoom = {{"livingroom", "qrc:/images/ic_livingroom.png"},
                                          {"bedroom", "qrc:/images/ic_bedroom.png"},
                                          {"bathroom", "qrc:/images/ic_bathroom.png"},
                                          {"other room", "qrc:/images/ic_otherroom.png"}};
};

GroupController::GroupController(QObject *parent)
    :QObject(parent),
      d_ptr(new Impl)
{
//    d_ptr->qZXing = new QZXing(this);
    d_ptr->listGroup = new ZListDataModel(this);
    d_ptr->groupManager = new GroupManager(this);
    d_ptr->deviceManager = new DeviceManager(this);
    d_ptr->groupService = new GroupService(this);
    d_ptr->listGroup->registerRoleNames(GroupDataModel::roleNames());
    d_ptr->groupManager = GlobalHandle::groupManager();
    d_ptr->groupManager->initialize();
    d_ptr->deviceManager = GlobalHandle::deviceManager();
    d_ptr->deviceManager->initialize();
//    d_ptr->qZXing = GlobalHandle::qzxing();

    for(QString& groupName: d_ptr->listRootRoomTitle) {
        QString groupAvatar = d_ptr->listRootRoom[groupName];
        this->setRootRoom(-1, enumGroupType::groupTypeRoot, groupName, groupAvatar);
    }
}

int GroupController::deleteGroup(int groupId, const QString& groupName) {
    qDebug() << "Start DELETE group, groupId: " + QString::number(groupId);
    std::list<ZGroup> groups = d_ptr->groupManager->getGroupList();
    int pos = -1;
    for (ZGroup& itemGroup : groups) {
        pos += 1;
        qDebug() << "itemGroup.groupId(): " + QString::number(itemGroup.groupId());
        if(itemGroup.groupId() == groupId) {
            d_ptr->listGroup->removeItem(pos);
            d_ptr->groupManager->removeGroup(groupId, groupName);
            break;
        }
    }
    return 0;
}

int GroupController::addGroup(const QString& groupName) {
    qDebug() << "Start ADD group";
//    QString str = d_ptr->qZXing->decodeImageFromFile("qrc:/images/qrcodetest.png", -1, -1, false);
//    qDebug() << "decodeImageFromFile: " + str;
    if(d_ptr->groupManager->getGroup(groupName).groupId() > 0)
    {
        qDebug() << "group [" +groupName + "] is existed";
        return -1;
    }

    //init group infomation
    int32_t groupId = -1;
    QString groupAvatar = "qrc:/images/ic_defaultroom.png";
    int32_t groupType = 0; //can delete
    ZGroup itemGroup;
    int32_t totalDeviceInGroup = 0;

    itemGroup.setGroupId(groupId);
    itemGroup.setGroupName(groupName);
    itemGroup.setGroupAvatar(groupAvatar);
    itemGroup.setGroupType(groupType);
    int result =d_ptr->groupManager->addGroup(itemGroup);
    qDebug() << "result add group: " + QString::number(result);
    if(result > 0)
    {
        ZAbstractRowDataModelPtr group(new GroupDataModel(result, groupName, groupAvatar, groupType, totalDeviceInGroup));
        d_ptr->listGroup->addItem(group);

    }
    return 0;
}

bool GroupController::checkGroupExisted(const QString& groupName) {
    if(d_ptr->groupManager->getGroup(groupName).groupId() >0) {
        qDebug() << "group [" +groupName + "] is existed";
        return true;
    }
    return false;
}

QAbstractListModel* GroupController::listGroup() const
{
    d_ptr->listGroup->clear();
    std::list<ZGroup> groups = d_ptr->groupManager->getGroupList();
    qDebug() << "total group: " + QString::number(groups.size());
    int32_t groupId = -1;
    QString groupName = "";
    QString groupAvatar = "";
    int32_t groupType = -1;
    int32_t totalDeviceInGroup = 0;

    for (ZGroup& itemGroup : groups) {
        groupId = itemGroup.groupId();
        groupName = itemGroup.groupName();
        groupAvatar = itemGroup.groupAvatar();
        groupType = itemGroup.groupType();
        totalDeviceInGroup = d_ptr->deviceManager->getDeviceList(groupName).size();
        ZAbstractRowDataModelPtr group(new GroupDataModel(groupId, groupName, groupAvatar, groupType, totalDeviceInGroup));
        d_ptr->listGroup->addItem(group);
    }
    return d_ptr->listGroup;
}

std::list<QString> GroupController::listGroupName() const {
    std::list<ZGroup> groups = d_ptr->groupManager->getGroupList();
    qDebug() << "total group: " + QString::number(groups.size());
    QString groupName = "";

    for (ZGroup& itemGroup : groups) {
        groupName = itemGroup.groupName();
        d_ptr->listGroupName.push_back(groupName);
    }
    return d_ptr->listGroupName;
}

void GroupController::setRootRoom(int32_t groupId,
                    int32_t groupType,
                    const QString& groupName,
                    const QString& groupAvatar) {
    ZGroup itemGroup;
    if(d_ptr->groupManager->getGroup(groupName).groupId() <= 0 )
    {
        itemGroup.setGroupId(groupId);
        itemGroup.setGroupName(groupName);
        itemGroup.setGroupAvatar(groupAvatar);
        itemGroup.setGroupType(groupType);
        d_ptr->groupManager->addGroup(itemGroup);
    }
}




