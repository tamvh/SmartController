#include <QSettings>
#include <QDebug>
#include <QQmlApplicationEngine>
#include <QtQml>
#include <QFontDatabase>
#include <QQuickWindow>

#include <vector>

#include <qmlcontrols.h>
#include <zlistmodel.h>
#include <db/updatabase.h>
#include "manager/devicemanager.h"
#include "manager/groupmanager.h"
#include "manager/devicecalendarmanager.h"
#include "manager/devicehardwareservice.h"
#include "controller/devicelistcontroller.h"
#include "controller/devicedetailcontroller.h"
#include "controller/devicecalendarcontroller.h"
#include "controller/devicescanningcontroller.h"
#include "controller/groupcontroller.h"
#include "controller/devicecontroller.h"
#include "QZXing.h"

#include "applicationinfo.h"

struct ApplicationInfo::ApplicationInfoPrivate
{
    ApplicationInfoPrivate(ApplicationInfo *app) :
        applicationDB(new DB::UPDatabase("database"))

    {
        Q_UNUSED(app);

        if (!applicationDB->open()) {
            qDebug() << "Cannot open application database";
        }

    }

    ~ApplicationInfoPrivate() {
    }
    void registerApplicationFonts()
    {
        // Load the embedded font.
        QString fontPath = ":/fonts/flaticon.ttf";
        int fontId = QFontDatabase::addApplicationFont(fontPath);
        if (fontId != -1) {
            qDebug() << "Flaticon is installed";
        }
    }

    void initializeApplicationContext()
    {
    }

    //! initialize objects/states that depend on ApplicationInfo::instance()::d_ptr
    void initializeApplicationObjects() {
//        cacheManager = std::shared_ptr<UPCache>(new UPCache());
        deviceManager->initialize();
        deviceCalendarManager->initialize();
    }
public:
    std::shared_ptr<DB::UPDatabase> applicationDB;
    std::shared_ptr<DeviceManager> deviceManager;
    std::shared_ptr<GroupManager> groupManager;
    std::shared_ptr<DeviceCalendarManager> deviceCalendarManager;
    std::shared_ptr<DeviceHardwareService> deviceHardwareService;
    std::shared_ptr<QZXing> qZXing;
};

ApplicationInfo *ApplicationInfo::self = 0;

ApplicationInfo::ApplicationInfo(QObject *parent):
    QObject(parent),
    d_ptr(new ApplicationInfoPrivate(this))
{
    qDebug()<<"____________________ALLOC_____"<<ApplicationInfo::applicationDB();
    Q_ASSERT_X(!self, "ApplicationInfo", "there should be only one application object");
    self = this;
    d_ptr->deviceManager = std::shared_ptr<DeviceManager>(new DeviceManager);
    d_ptr->groupManager = std::shared_ptr<GroupManager>(new GroupManager);
    d_ptr->deviceCalendarManager = std::shared_ptr<DeviceCalendarManager>(new DeviceCalendarManager());
    d_ptr->deviceHardwareService = std::shared_ptr<DeviceHardwareService>(new DeviceHardwareService());
    d_ptr->qZXing = std::shared_ptr<QZXing>(new QZXing());
}

void ApplicationInfo::applicationStartup()
{
    d_ptr->initializeApplicationObjects();
    d_ptr->registerApplicationFonts();
    d_ptr->initializeApplicationContext();

    qmlRegisterType<DeviceListController>("SmartControls", 1, 0, "DeviceListController");
    qmlRegisterType<DeviceDetailController>("SmartControls", 1, 0, "DeviceDetailController");
    qmlRegisterType<DeviceCalendarController>("SmartControls", 1, 0, "DeviceCalendarController");
    qmlRegisterType<DeviceScanningController>("SmartControls", 1, 0, "DeviceScanningController");
    qmlRegisterType<GroupController>("SmartControls", 1, 0, "GroupController");
    qmlRegisterType<DeviceController>("SmartControls", 1, 0, "DeviceController");
    qmlRegisterType<QZXing>("SmartControls", 1, 0, "QZXing");
}

void ApplicationInfo::start(const QString &qmlFile)
{
    QQmlApplicationEngine *engine = new QQmlApplicationEngine(this);
    engine->addImportPath("qrc:///");
    QmlControls::registerTypes();
    ZListModel::registerTypes();
//    engine->rootContext()->setContextProperty("User", d_ptr->userInfo);
    engine->load(QUrl(qmlFile));

    QQuickWindow *window = qobject_cast<QQuickWindow *>(engine->rootObjects().first());

    /// Setup the QQuickWindow instance to fit the iOS environment
    QmlControls::setupWindow(window);
    QmlControls::setStatusBarStyle(QmlControls::StatusBarStyleDefault);

    QObject *topLevel = engine->rootObjects().value(0);
    QVariant nullContext;
    QMetaObject::invokeMethod(topLevel, "init", Qt::QueuedConnection, Q_ARG(QVariant, nullContext));
}

DB::UPDatabase *ApplicationInfo::applicationDB() const
{
    return d_ptr->applicationDB.get();
}

DeviceManager *ApplicationInfo::deviceManager() const
{
    return d_ptr->deviceManager.get();
}

GroupManager *ApplicationInfo::groupManager() const
{
    return d_ptr->groupManager.get();
}

DeviceCalendarManager *ApplicationInfo::deviceCalendarManager() const
{
    return d_ptr->deviceCalendarManager.get();
}

DeviceHardwareService* ApplicationInfo::deviceHardwareService() const
{
    return d_ptr->deviceHardwareService.get();
}

QZXing* ApplicationInfo::qzxing() const
{
    return d_ptr->qZXing.get();
}

