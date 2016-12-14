#include <map>
#include <list>
#include <QDebug>
#include <QSharedPointer>
#include <QDateTime>
#include <QCoreApplication>
#include <QtAndroidExtras/QAndroidJniObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QtNetwork/QNetworkRequest>
#include <QtNetwork/QNetworkReply>
#include <QUrl>
#include <QObject>
#include <QString>
#include "zlistdatamodel.h"
#include "../configuration.h"
#include "src/app_commons.h"
#include "src/model/zvalue.h"
#include <src/manager/commonmanager.h>
#include "initcontroller.h"

class InitController::Impl {
public:
    CommonManager *commonManager;
};

InitController::InitController(QObject* parent)
    : QObject(parent),
      d_ptr(new Impl)
{
    d_ptr->commonManager = GlobalHandle::commonManager();
    d_ptr->commonManager->initialize();
}

int InitController::setValue(const QString &key, const QString &value) {
    qDebug() << Q_FUNC_INFO;
    ZValue zvalue;
    zvalue.setId(-1);
    zvalue.setKey(key);
    zvalue.setValue(value);
    int result = d_ptr->commonManager->insertValue(zvalue);
    if(result > 0)
    {
        qDebug() << Q_FUNC_INFO << "Insert Value success!!!";
        return result;
    }
    return 0;
}

QString InitController::getValue(const QString& key) {
    QString value = "";
    ZValue zvalue = d_ptr->commonManager->getValue(key);
    value = zvalue.getValue();
    return value;
}
