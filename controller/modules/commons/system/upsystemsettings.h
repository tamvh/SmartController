#ifndef SMARTTHINGS_UPSYSTEMSETTINGS_H
#define SMARTTHINGS_UPSYSTEMSETTINGS_H

#include <QObject>

class UPSystemSettings : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int apiDispatcherIndex READ apiDispatcherIndex NOTIFY apiDispatcherIndexChanged)
    Q_PROPERTY(bool debugMode READ debugMode NOTIFY debugModeChanged)
public:
    explicit UPSystemSettings(QObject *parent = 0);
    ~UPSystemSettings();
public:
    int apiDispatcherIndex() const;
    Q_INVOKABLE void changeAPIDispatcher(int index);

    bool debugMode() const;
    Q_INVOKABLE void changeDebugMode(bool value);
signals:
    void apiDispatcherIndexChanged();
    void debugModeChanged();
public slots:
};

#endif // SMARTTHINGS_UPSYSTEMSETTINGS_H
