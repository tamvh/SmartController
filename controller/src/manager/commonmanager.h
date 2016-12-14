#ifndef COMMONMANAGER_H
#define COMMONMANAGER_H

#include <vector>
#include <QSharedPointer>
#include <QString>
class ZValue;
class CommonManager : public QObject
{
    Q_OBJECT
public:
    explicit CommonManager(QObject* parent = 0);
    ~CommonManager();
public:
    void initialize();
public:
    int32_t insertValue(ZValue& value);
    bool updateValue(ZValue& value);
    void removeValue(const QString& key);
    ZValue getValue(const QString& key);
signals:
    void commonListChanged();
private:
    class Impl;
    QSharedPointer<Impl> d_ptr;
};

#endif // COMMONMANAGER_H
