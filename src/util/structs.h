//
// Created by Jack Hester on 6/13/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H

//struct to store valve states as bool
struct valves {
    bool loxPressurant;
    bool kerPressurant;
    bool loxPurge;
    bool kerPurge;
    bool loxVent;
    bool kerVent;
    bool loxFlow;
    bool kerFlow;
    //TODO: note that lox and ker drip are not controlled pneumatically now, just manually
    bool loxDrip;
    bool kerDrip;
};

//struct to store sensor values/readings
struct sensors {
    double loxInletDucer;
    double kerInletDucer;
    double purgeDucer;
    double kerPintleDucer;
    double loxTankDucer;
    double kerTankDucer;
    double pneumaticDucer;
    double loxN2Ducer;
    double kerN2Ducer;
    double loxVenturi;
    double kerVenturi;
    double manifoldInletThermo;
    double manifoldOutletThermo;
    double tank1Thermo;
    double tank2Thermo;
    double tank3Thermo;
    double loadCell;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H
