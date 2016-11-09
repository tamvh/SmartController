#include "zuser.h"

class ZUser::Impl {
public:
    QString userName;
    QString email;
    QString userId;
    QString gender;
};

ZUser::ZUser(): d_ptr(new Impl) {
}

ZUser::ZUser(const QString& userId) : d_ptr(new Impl) {
    d_ptr->userId = userId;
}

ZUser::ZUser(const ZUser& other) : d_ptr(other.d_ptr) {
}

QString ZUser::userName() const {
    return d_ptr->userName;
}
void ZUser::setUserName(const QString& userName) {
    d_ptr->userName = userName;
}
QString ZUser::email() const {
    return d_ptr->email;
}
void ZUser::setEmail(const QString& email) {
    d_ptr->email = email;
}
QString ZUser::userId() const {
    return d_ptr->userId;
}
void ZUser::setUserId(const QString& userId) {
    d_ptr->userId = userId;
}
QString ZUser::gender() const {
    return d_ptr->gender;
}
void ZUser::setGender(const QString& gender) {
    d_ptr->gender = gender;
}
