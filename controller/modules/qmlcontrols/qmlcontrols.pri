QT += qml quick svg

QML_IMPORT_PATH += $$PWD

INCLUDEPATH += $$PWD

RESOURCES += $$PWD/QmlControls/qmlcontrols.qrc
#             $$PWD/QmlControls/material.qrc

OTHER_FILES += $$PWD/QmlControls/qmldir
#               $$PWD/QmlControls/Material/qmldir
ios {
    #Qt Quick Controls
#    QTPLUGIN += qtquickcontrolsplugin

    OBJECTIVE_SOURCES += $$PWD/ios_plugin.mm

    # Fix for linking issues for Qt 5.3.2
    QTQUICKCONTROLS_LIBS = -L$$clean_path($$QMAKESPEC/../../qml/QtQuick/Controls)
    QTQMLMODELS_LIBS = -L$$clean_path($$QMAKESPEC/../../qml/QtQml/Models.2)
    LIBS += $$QTQUICKCONTROLS_LIBS $$QTQMLMODELS_LIBS -lmodelsplugin

    QMAKE_POST_LINK += /usr/libexec/PlistBuddy -c \"Add :UIViewControllerBasedStatusBarAppearance bool false\" $${OUT_PWD}/Info.plist
}

HEADERS += \
    $$PWD/qmlcontrols.h \
    $$PWD/qmlunit.h \
    $$PWD/qmlcss.h \
    $$PWD/qmldevice.h

SOURCES += \
    $$PWD/qmlcontrols.cpp \
    $$PWD/qmlunit.cpp \
    $$PWD/qmlcss.cpp \
    $$PWD/qmldevice.cpp

