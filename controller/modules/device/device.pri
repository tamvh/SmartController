QT += qml quick widgets
INCLUDEPATH += $$PWD
QML_IMPORT_PATH += $$PWD

RESOURCES += \
    $$PWD/Device/device.qrc
DISTFILES += \
    $$PWD/Device/qmldir

HEADERS += \
    $$PWD/devicelistcontroller.h \
    $$PWD/datamodel/devicedatamodel.h \
    $$PWD/device.h \
    $$PWD/manager/devicemanager.h \
    $$PWD/manager/devicemodel.h

SOURCES += \
    $$PWD/devicelistcontroller.cpp \
    $$PWD/datamodel/devicedatamodel.cpp \
    $$PWD/device.cpp \
    $$PWD/manager/devicemanager.cpp
