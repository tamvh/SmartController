#ifndef ZGROUP_H
#define ZGROUP_H
#include <cstdint>
#include <memory>
#include <vector>
#include <QString>

class ZGroup
{
public:
    ZGroup();
    ZGroup(const int32_t& groupId);
    ZGroup(const ZGroup& other);
    ZGroup& operator=(const ZGroup& other);
    bool operator==(const ZGroup& other) const;
    bool operator==(const int32_t groupId) const;

    int32_t groupId() const;
    void setGroupId(int32_t groupId);
    QString groupName() const;
    void setGroupName(const QString& groupName);
    QString groupAvatar() const;
    void setGroupAvatar(const QString& groupAvatar);
    int32_t groupType() const;
    void setGroupType(int32_t groupType);
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

inline bool operator==(const ZGroup &a1, const int32_t &a2)
{ return a1.groupId() == a2; }
inline bool operator==(const int32_t &a2, const ZGroup &a1)
{ return a1.groupId() == a2; }


#endif // ZGROUP_H
