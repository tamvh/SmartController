TEMPLATE=app
TARGET=SmartLamp

QT += quick qml core sql xml bluetooth

CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

include(../modules/commons/commons.pri)
include(../modules/qmlcontrols/qmlcontrols.pri)
include(../modules/qmlmaterial/qmlmaterial.pri)
include(../modules/zlistview/zlistview.pri)
include(../modules/qmlitem/qmlitem.pri)
#include(../modules/ble/ble.pri)

ios: include(ios/ios.pri)
macx: include(mac/mac.pri)
android: include(android/android.pri)

INCLUDEPATH += $$PWD
RESOURCES += main.qrc

SOURCES += \
    applicationinfo.cpp \
    main.cpp \
    app_global.cpp \
    configuration.cpp \
    manager/devicemanager.cpp \
    manager/devicecalendarmanager.cpp \
    manager/devicescannerservice.cpp \
    model/zdevice.cpp \
    model/zdevicedata.cpp \
    controller/devicelistcontroller.cpp \
    controller/devicecalendarcontroller.cpp \
    datamodel/devicecalendardatamodel.cpp \
    datamodel/devicedatamodel.cpp \
    model/zdevicecalendaritem.cpp \
    controller/devicedetailcontroller.cpp \
    controller/devicescanningcontroller.cpp \
    datamodel/scanneddevicedatamodel.cpp \
    db/devicecalendardb.cpp \
    db/zdevicedb.cpp \
    controller/devicehardwarecontroller.cpp \
    model/zstackbright.cpp \
    manager/bluetooth/bluetoothservice.cpp \
    manager/bluetooth/bluetoothcharacteristic.cpp \
    manager/bluetooth/bluetoothoperation.cpp \
    manager/devicehardwareservice.cpp \
    manager/bluetooth/bluetoothcontroller.cpp \
    manager/bluetooth/bluetoothadvertising.cpp

HEADERS += \
    app_commons.h \
    applicationinfo.h \
    configuration.h \
    manager/devicemanager.h \
    manager/devicecalendarmanager.h \
    manager/devicescannerservice.h \
    model/zdevice.h \
    model/zdevicedata.h \
    controller/devicelistcontroller.h \
    controller/devicecalendarcontroller.h \
    datamodel/devicecalendardatamodel.h \
    datamodel/devicedatamodel.h \
    model/zdevicecalendaritem.h \
    controller/devicedetailcontroller.h \
    controller/devicescanningcontroller.h \
    datamodel/scanneddevicedatamodel.h \
    db/devicecalendardb.h \
    db/zdevicedb.h \
    manager/devicehardwareservice.h \
    controller/devicehardwarecontroller.h \
    model/zstackbright.h \
    manager/bluetooth/bluetoothservice.h \
    manager/bluetooth/bluetoothcharacteristic.h \
    manager/bluetooth/bluetoothoperation.h \
    manager/bluetooth/bluetoothcontroller.h \
    manager/bluetooth/bluetoothadvertising.h

DISTFILES += \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    android/gradle/wrapper/gradle-wrapper.jar \
    manager/bluetooth/logs.txt \
    logs.txt

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
