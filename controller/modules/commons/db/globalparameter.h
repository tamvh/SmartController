#ifndef SMARTTHINGS_GLOBALPARAMETER_H
#define SMARTTHINGS_GLOBALPARAMETER_H

#include <QVariant>
#include <QString>
#include <memory>

class GlobalParameterBase {
public:
    GlobalParameterBase(const QString &key, const QVariant& defaultValue);
public:
    QVariant value();
    void setValue(const QVariant& v);
private:
    QVariant m_value;
    bool m_hasValue = false;
    QString m_key;
};

class GlobalParameterSet {
public:
    GlobalParameterSet(const QString &group);
public:
    QVariant value(const QString &key);
    void setValue(const QString &key, const QVariant& v);
private:
    QString m_group;
    struct Private;
    std::shared_ptr<Private> d;
};

template<typename T>
class GlobalParameter : public GlobalParameterBase {
public:
    //using GlobalParameterBase::GlobalParameterBase;
    operator T() {
        return value().template value<T>();
    }
    T operator = (const T& v) {
        setValue(v);
        return value().template value<T>();
    }
};

#endif // SMARTTHINGS_GLOBALPARAMETER_H
