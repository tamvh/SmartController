TEMPLATE = app
TARGET = SmartLamp
QT += quick qml core sql xml bluetooth quickcontrols2 gui charts widgets androidextras multimedia multimediawidgets network

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(QZXing_sourceV2.4/QZXing.pri)
include(modules/commons/commons.pri)
include(modules/qmlcontrols/qmlcontrols.pri)
include(modules/qmlmaterial/qmlmaterial.pri)
include(modules/zlistview/zlistview.pri)
include(modules/qmlitem/qmlitem.pri)

ios: include(src/ios/ios.pri)
macx: include(src/mac/mac.pri)
android: include(src/android/android.pri)

SOURCES += \
    controller.cpp \
    src/applicationinfo.cpp \
    src/app_global.cpp \
    src/configuration.cpp \
    src/manager/devicemanager.cpp \
    src/manager/devicecalendarmanager.cpp \
    src/manager/devicescannerservice.cpp \
    src/model/zdevice.cpp \
    src/model/zdevicedata.cpp \
    src/controller/devicelistcontroller.cpp \
    src/controller/devicecalendarcontroller.cpp \
    src/datamodel/devicecalendardatamodel.cpp \
    src/datamodel/devicedatamodel.cpp \
    src/model/zdevicecalendaritem.cpp \
    src/controller/devicedetailcontroller.cpp \
    src/controller/devicescanningcontroller.cpp \
    src/datamodel/scanneddevicedatamodel.cpp \
    src/db/devicecalendardb.cpp \
    src/db/zdevicedb.cpp \
    src/controller/devicehardwarecontroller.cpp \
    src/model/zstackbright.cpp \
    src/manager/bluetooth/bluetoothservice.cpp \
    src/manager/bluetooth/bluetoothcharacteristic.cpp \
    src/manager/bluetooth/bluetoothoperation.cpp \
    src/manager/devicehardwareservice.cpp \
    src/manager/bluetooth/bluetoothcontroller.cpp \
    src/manager/bluetooth/bluetoothadvertising.cpp \
    src/controller/groupcontroller.cpp \
    src/model/zgroup.cpp \
    src/controller/devicecontroller.cpp \
    src/manager/groupservice.cpp \
    src/datamodel/groupdatamodel.cpp \
    src/model/zdeviceingroup.cpp \
    src/db/zgroupdb.cpp \
    src/manager/groupmanager.cpp \
    QZXingFilter.cpp \
    src/model/zuser.cpp \
    src/controller/logincontroller.cpp

HEADERS += \
    src/app_commons.h \
    src/applicationinfo.h \
    src/configuration.h \
    src/manager/devicemanager.h \
    src/manager/devicecalendarmanager.h \
    src/manager/devicescannerservice.h \
    src/model/zdevice.h \
    src/model/zdevicedata.h \
    src/controller/devicelistcontroller.h \
    src/controller/devicecalendarcontroller.h \
    src/datamodel/devicecalendardatamodel.h \
    src/datamodel/devicedatamodel.h \
    src/model/zdevicecalendaritem.h \
    src/controller/devicedetailcontroller.h \
    src/controller/devicescanningcontroller.h \
    src/datamodel/scanneddevicedatamodel.h \
    src/db/devicecalendardb.h \
    src/db/zdevicedb.h \
    src/manager/devicehardwareservice.h \
    src/controller/devicehardwarecontroller.h \
    src/model/zstackbright.h \
    src/manager/bluetooth/bluetoothservice.h \
    src/manager/bluetooth/bluetoothcharacteristic.h \
    src/manager/bluetooth/bluetoothoperation.h \
    src/manager/bluetooth/bluetoothcontroller.h \
    src/manager/bluetooth/bluetoothadvertising.h \
    src/controller/groupcontroller.h \
    src/model/zgroup.h \
    src/controller/devicecontroller.h \
    src/manager/groupservice.h \
    src/datamodel/groupdatamodel.h \
    src/model/zdeviceingroup.h \
    src/db/zgroupdb.h \
    src/manager/groupmanager.h \
    QZXingFilter.h \
    src/model/zuser.h \
    src/controller/logincontroller.h

OTHER_FILES += \
    controller.qml \
    pages/*.qml

RESOURCES += \
    controller.qrc

INSTALLS += target

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/src/org/qtproject/lamp/MainActivity.java \
    android/src/org/qtproject/lamp/BroadcastSend.java \
    android/src/org/qtproject/lamp/BroadcastReceive.java \
    android/src/org/qtproject/lamp/AdvertiserService.java \
    android/src/org/qtproject/lamp/Common.java \
    android/src/org/qtproject/lamp/DeviceScanActivity.java \
    android/src/org/qtproject/lamp/LampApplication.java \
    android/src/org/qtproject/lamp/User.java \
    android/src/org/qtproject/lamp/PrefUtils.java \
    android/src/org/qtproject/lamp/ComplexPreferences.java \
    pages/Common.js


ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android


