#include <map>
#include <list>
#include <QDebug>
#include <src/model/zvalue.h>
#include "src/db/zcommondb.h"
#include "commonmanager.h"

namespace {
    typedef std::map<int32_t, ZValue> ZValueMap;
    typedef ZValueMap::iterator ZValueMapIterator;
    typedef std::map<QString, ZValue> ZValueMapStr;
    typedef ZValueMapStr::iterator ZValueMapIteratorStr;
    typedef std::list<ZValue> ZValueList;
    typedef ZValueList::iterator ZValueListIterator;
}

class CommonManager::Impl {
public:
    ZValueMap valueCollection;
    ZValueMapStr valueCollectionStr;
    ZValueList valueList;
    std::shared_ptr<ZCommonDB> commonDB;
    Impl() {
        qDebug() << Q_FUNC_INFO;
        commonDB = std::shared_ptr<ZCommonDB>(new ZCommonDB);
    }
};

CommonManager::CommonManager(QObject* parent) :
    QObject(parent),
    d_ptr(new Impl)
{
    qDebug() << Q_FUNC_INFO;
}

CommonManager::~CommonManager()
{
}

void CommonManager::initialize() {
    qDebug() << Q_FUNC_INFO;
    std::vector<QVariantMap> valuesVector = d_ptr->commonDB.get()->getValues();
    qDebug() << Q_FUNC_INFO << "valuesVector.size():" << valuesVector.size();
    if (valuesVector.size() <= 0) {
        return;
    }

    d_ptr->valueList.clear();
    d_ptr->valueCollection.clear();
    d_ptr->valueCollectionStr.clear();
    for (QVariantMap const& valueVariant: valuesVector) {
        int id = valueVariant["id"].toInt();
        QString key = valueVariant["zkey"].toString();
        QString value = valueVariant["zvalue"].toString();
        qDebug() << Q_FUNC_INFO << "id:" << id;
        qDebug() << Q_FUNC_INFO << "key:" << key;
        qDebug() << Q_FUNC_INFO << "value:" << value;
        ZValue zvalue;
        zvalue.setId(static_cast<int32_t>(id));
        zvalue.setKey(key);
        zvalue.setValue(value);
        d_ptr->valueList.push_back(zvalue);
        d_ptr->valueCollection[zvalue.getId()] = zvalue;
        d_ptr->valueCollectionStr[zvalue.getKey()] = zvalue;
    }
}

int32_t CommonManager::insertValue(ZValue& value) {
    // add group to db
    int result = d_ptr->commonDB.get()->insertValue(value);
    if (result <= 0) {
        //insertOrReplaceGroup fail
        qDebug() << Q_FUNC_INFO << "insertValue fail, result:" << result;
        return result;
    }
    // update new id
    value.setId(result);
    const ZValue& valueTmp = value;
    d_ptr->valueCollection.insert(std::pair<int32_t, ZValue>(result, valueTmp));
    d_ptr->valueCollectionStr.insert(std::pair<QString, ZValue>(valueTmp.getKey(), valueTmp));
    d_ptr->valueList.push_back(value);
    // signal new group added
    emit commonListChanged();
    return value.getId();
}

bool CommonManager::updateValue(ZValue& value) {
    int result = d_ptr->commonDB.get()->updateValue(value);
    if (!result) {
        //update faile
        qDebug() << Q_FUNC_INFO << "insertValue fail, result: " << result;
        return result;
    }
    // update new id
    value.setId(result);
    const ZValue& valueTmp = value;
    d_ptr->valueCollection.insert(std::pair<int32_t, ZValue>(result, valueTmp));
    d_ptr->valueCollectionStr.insert(std::pair<QString, ZValue>(valueTmp.getKey(), valueTmp));
    d_ptr->valueList.push_back(value);
    // signal new group added
    emit commonListChanged();
    return true;
}

void CommonManager::removeValue(const QString& key) {
    // remove from db
    bool result = d_ptr->commonDB.get()->removeValue(key);
    // signal zvalue removed
    if (!result) {
        qDebug() << Q_FUNC_INFO << "removeValue fail, result:" << result;
    }
    emit commonListChanged();
}

ZValue CommonManager::getValue(const QString& key) {
    ZValueMapIteratorStr itFind = d_ptr->valueCollectionStr.find(key);
    if (itFind == d_ptr->valueCollectionStr.end()) {
        return ZValue();
    } else {
        return itFind->second;
    }
}




