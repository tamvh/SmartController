#ifndef LOGINCONTROLLER_H
#define LOGINCONTROLLER_H
#include <QDebug>
#include <QObject>
#include <QSharedPointer>
#include <QAbstractListModel>


class ZUser;
class LoginController : public QObject
{
    Q_OBJECT
public:
    explicit LoginController(QObject *parent = 0);
public slots:
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // LOGINCONTROLLER_H
