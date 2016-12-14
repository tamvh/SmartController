#ifndef ZVALUE_H
#define ZVALUE_H

#include <QString>
#include <memory>
class ZValue
{
public:
    ZValue();
    ZValue(int32_t id);
    ~ZValue();
public:
    void setId(int32_t id);
    int32_t getId();

    void setKey(const QString& key);
    QString getKey() const;

    void setValue(const QString& value);
    QString getValue() const;
private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // ZVALUE_H
