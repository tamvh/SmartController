#ifndef APPLICATIONINFO_H
#define APPLICATIONINFO_H

#include <QObject>
#include <memory>

namespace DB {
class UPDatabase;
}

class CommonManager;
class DeviceManager;
class GroupManager;
class DeviceCalendarManager;
class DeviceHardwareService;
class QZXing;
class HttpClient;

class ApplicationInfo : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY(ApplicationInfo)
public:
    explicit ApplicationInfo(QObject *parent = 0);
    static ApplicationInfo *instance() { return self; }

    void applicationStartup();
    void start(const QString &qmlFile);

    DB::UPDatabase *applicationDB() const;
    CommonManager* commonManager() const;
    DeviceManager* deviceManager() const;
    GroupManager* groupManager() const;
    DeviceCalendarManager* deviceCalendarManager() const;
    DeviceHardwareService* deviceHardwareService() const;
    QZXing* qzxing() const;
    HttpClient* httclient() const;
private:
    static ApplicationInfo *self;
    struct ApplicationInfoPrivate;
    std::shared_ptr<ApplicationInfoPrivate> d_ptr;
};

#endif // APPLICATIONINFO_H
