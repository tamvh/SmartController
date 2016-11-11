#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include <QString>

namespace Configuration {
    extern QString ServiceId;
    extern QString CharacteristicId;
    extern QString readPlugStateCharId;
    extern QString updateTimeCharId;
    extern int TurnOffLamp;
    extern int TurnOnLamp;
    extern QString hostServer;
    extern int portServer;
}

#endif // CONFIGURATION_H
