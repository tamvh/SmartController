#include "zgroup.h"

class ZGroup::Impl {
public:
    int32_t _groupId;
    QString _groupName;
    QString _groupAvatar;
    int32_t _groupType;
};

ZGroup::ZGroup()
: d_ptr(new Impl) {
}

ZGroup::ZGroup(const int32_t& groupId) : d_ptr(new Impl){
    d_ptr->_groupId = groupId;
}

ZGroup::ZGroup(const ZGroup& other) : d_ptr(other.d_ptr){
}

ZGroup& ZGroup::operator=(const ZGroup& other) {
    d_ptr = other.d_ptr;
    return *this;
}

bool ZGroup::operator==(const ZGroup& other) const {
    return d_ptr->_groupId == other.groupId();
}

bool ZGroup::operator==(const int32_t groupId) const {
    return d_ptr->_groupId == groupId;
}

int32_t ZGroup::groupId() const {
    return d_ptr->_groupId;
}
void ZGroup::setGroupId(int32_t groupId) {
    d_ptr->_groupId = groupId;
}
QString ZGroup::groupName() const {
    return d_ptr->_groupName;
}
void ZGroup::setGroupName(const QString& groupName) {
    d_ptr->_groupName = groupName;
}
QString ZGroup::groupAvatar() const {
    return d_ptr->_groupAvatar;
}
void ZGroup::setGroupAvatar(const QString& groupAvatar) {
    d_ptr->_groupAvatar = groupAvatar;
}
int32_t ZGroup::groupType() const {
    return d_ptr->_groupType;
}
void ZGroup::setGroupType(int32_t groupType) {
    d_ptr->_groupType = groupType;
}


