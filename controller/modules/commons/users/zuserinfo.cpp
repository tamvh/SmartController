#include <QDebug>
#include <QSharedPointer>
#include <QSettings>

#include "zuserinfo.h"
#include "db/globalparameter.h"

class ZUserInfoPrivate
{
public:
    ZUserInfoPrivate() {
    }

public:
    QString userName;
    QString displayName;
    QString avatarUrl;
    quint64 userID;
    QString sessionKey;
};

ZUserInfo::ZUserInfo(QObject *parent) :
    QObject(parent),
    p(new ZUserInfoPrivate)
{
}

ZUserInfo::~ZUserInfo()
{
    delete p;
}

void ZUserInfo::logout()
{
    GlobalParameterSet currentUser("currentuser");
    currentUser.setValue("userId", 0);
    currentUser.setValue("userName", "");
    currentUser.setValue("displayName", "");
    currentUser.setValue("avatar", "");
    currentUser.setValue("session", "");

    p->userID = 0;
    p->userName = "";
    p->displayName = "";
    p->avatarUrl = "";
    p->sessionKey = "";

    emit userNameChanged();
    emit avatarChanged();
    emit displayNameChanged();
    emit userIDChanged();
    emit userSessionChanged();

    emit isValidChanged();
}

bool ZUserInfo::reloadCurrentUser()
{
    p->userID = 0;

    GlobalParameterSet currentUser("currentuser");
    p->userID = currentUser.value("userId").toULongLong();
    if (p->userID == 0) {
        return false;
        emit loadUserInfoError();
    }

    p->userName = currentUser.value("userName").toString();
    p->displayName = currentUser.value("displayName").toString();
    p->avatarUrl = currentUser.value("avatar").toString();
    p->sessionKey = currentUser.value("session").toString();

    emit userNameChanged();
    emit avatarChanged();
    emit displayNameChanged();
    emit userIDChanged();
    emit userSessionChanged();

    emit loadUserInfoSuccess();
    emit isValidChanged();

    return true;
}

bool ZUserInfo::isLoggedIn() const
{
    return (p->userID > 0);
}

bool ZUserInfo::hasValidUserInfo() const
{
    return p->userID > 0 && !p->userName.isEmpty();
}

QString ZUserInfo::userName() const
{
    return p->userName;
}

QString ZUserInfo::avatar() const
{
    return p->avatarUrl;
}

QString ZUserInfo::displayName() const
{
    return p->displayName;
}

QString ZUserInfo::userSession() const
{
    return p->sessionKey;
}

quint64 ZUserInfo::userID() const
{
    return p->userID;
}

