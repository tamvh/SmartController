#include <QDebug>

#include "upsystemsettings.h"

UPSystemSettings::UPSystemSettings(QObject *parent) : QObject(parent)
{

}

UPSystemSettings::~UPSystemSettings()
{

}

int UPSystemSettings::apiDispatcherIndex() const
{
    return 0;
}

void UPSystemSettings::changeAPIDispatcher(int index)
{
    Q_UNUSED(index);
}

bool UPSystemSettings::debugMode() const
{
    return true;
}

void UPSystemSettings::changeDebugMode(bool value)
{
    Q_UNUSED(value);
}
