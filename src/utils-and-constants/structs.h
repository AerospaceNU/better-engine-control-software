//
// Created by Jack Hester on 6/13/22.
//
#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H

#include <cstdint>

namespace PhysBoundary {
    //TODO: do we really need the Sensors, States, and Effectors structs? i think the current SensorData and CommandData works
    //struct to store (valve) states as bools
    typedef struct __attribute__((__packed__)) {
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
    } States;

    //struct to store sensor values/readings
    typedef struct __attribute__((__packed__)) {
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
    } Sensors;

    //structs for effectors to store things they should change (effect)
    typedef struct __attribute__((packed)) {
        bool state1;
    } Effectors;


    //------NB: WrappedPacket and TeensyData mirror the code on the teensy-----//

    //struct to hold data received from Teensy
    typedef struct __attribute__((__packed__)) TeensyData {
        int16_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8, adc9, adc10, adc11;
        int32_t loadCell0;
        double tc0, tc1, tc2, tc3, tc4, tc5, tc6, tc7;
    } TeensyData;

    //Struct to //TODO: add description of packetCRC
    typedef struct __attribute__((__packed__)) WrappedPacket {
        TeensyData dataPacket;
        uint16_t packetCRC;
    } WrappedPacket;
}

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_STRUCTS_H
