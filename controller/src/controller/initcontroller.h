#ifndef INITCONTROLLER_H
#define INITCONTROLLER_H

#include <QString>
#include <memory>
#include <QObject>
#include <QSharedPointer>
class InitController : public QObject
{
    Q_OBJECT
public:
    explicit InitController(QObject *parent = 0);
public slots:
    Q_INVOKABLE int setValue(const QString& key, const QString& value);
    Q_INVOKABLE QString getValue(const QString& key);
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // INITCONTROLLER_H
