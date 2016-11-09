#include <map>
#include <list>
#include <QDebug>
#include <QSharedPointer>
#include <QDateTime>
#include <QtAndroidExtras/QAndroidJniObject>
#include "src/model/zuser.h"
#include "logincontroller.h"

class LoginController::Impl {
public:
    ZUser* user;
};

LoginController::LoginController(QObject *parent)
    : QObject(parent),
    d_ptr(new Impl) {
}

