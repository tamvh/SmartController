#include "zvalue.h"

class ZValue::Impl {
public:
    int32_t id;
    QString key;
    QString value;
};

ZValue::ZValue() : d_ptr(new Impl)
{
}

ZValue::ZValue(int32_t id) : d_ptr(new Impl)
{
    d_ptr->id = id;
}

ZValue::~ZValue()
{
}

void ZValue::setId(int32_t id) {
    d_ptr->id = id;
}

int32_t ZValue::getId() {
    return d_ptr->id;
}

void ZValue::setKey(const QString& key) {
    d_ptr->key = key;
}

QString ZValue::getKey() const {
    return d_ptr->key;
}

void ZValue::setValue(const QString& value) {
    d_ptr->value = value;
}

QString ZValue::getValue() const {
    return d_ptr->value;
}



