QT += qml quick svg

QML_IMPORT_PATH += $$PWD

INCLUDEPATH += $$PWD

RESOURCES += $$PWD/FontAwesome.qrc \
             $$PWD/Icons.qrc \
             $$PWD/Material.qrc \
             $$PWD/FontRoboto.qrc \
             $$PWD/MaterialQtQuick.qrc

OTHER_FILES += $$PWD/QmlControls/qmldir \
               $$PWD/QmlControls/Material/qmldir
