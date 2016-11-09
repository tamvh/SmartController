#ifndef ZUSER_H
#define ZUSER_H
#include <cstdint>
#include <memory>
#include <vector>
#include <QString>

class ZUser
{
public:
    ZUser();
    ZUser(const QString& userId);
    ZUser(const ZUser& other);
public:
    QString userName() const;
    void setUserName(const QString& userName);
    QString email() const;
    void setEmail(const QString& email);
    QString userId() const;
    void setUserId(const QString& userId);
    QString gender() const;
    void setGender(const QString& gender);

private:
    class Impl;
    std::shared_ptr<Impl> d_ptr;
};

#endif // ZUSER_H
