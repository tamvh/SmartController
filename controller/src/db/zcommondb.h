#ifndef ZCOMMONDB_H
#define ZCOMMONDB_H

#include <QObject>
#include <memory>

class ZValue;
class ZCommonDB
{
public:
    ZCommonDB();
    ~ZCommonDB();
public:
    std::vector<QVariantMap> getValues();
    std::vector<QVariantMap> getValues(const QString& key);
    ZValue getLatestValue();
    ZValue getValueItem(const QString& key);
    int insertValue(ZValue& value);
    bool updateValue(ZValue& value);
    bool removeValue(const QString& key);
private:
    class Private;
    std::shared_ptr<Private> d_ptr;
};

#endif // ZCOMMONDB_H
