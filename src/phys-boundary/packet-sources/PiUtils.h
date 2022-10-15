//
// Created by Cameron on 5/13/21.
//

#ifndef ENGINECONTROLSYSTEM_PIUTILS_H
#define ENGINECONTROLSYSTEM_PIUTILS_H

#include <cstdint>

// TODO: we have these structs duplicated in the separate ecs-utils repo. maybe merge the two together, so they can
// share the same struct definition?
/**
 * Packed struct for data Teensy Arduino sends over serial
 */
typedef struct __attribute__((__packed__)) TeensyData {
    int16_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8, adc9, adc10, adc11;
    int32_t loadCell0;
    double tc0, tc1, tc2, tc3, tc4, tc5, tc6, tc7;
} TeensyData;

/**
 * Packed struct containing teensy data as well as a verification number
 * to check for data correctness
 */
typedef struct __attribute__((__packed__)) WrappedPacket {
    TeensyData dataPacket;
    uint16_t packetCRC;
} WrappedPacket;

/**
 * Packed struct containing data from ADCS as well as a verification number
 * to check for data correctness
 */
typedef struct __attribute__((__packed__)) AdcBreakoutSensorData {
    int16_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8, adc9, adc10, adc11;
    uint16_t packetCRC;
} AdcBreakoutSensorData;

typedef struct __attribute__((__packed__)) PropBoardSensorData {
    uint32_t timestamp;
    int32_t adc0, adc1, adc2, adc3, adc4, adc5, adc6, adc7, adc8, adc9, adc10, adc11, adc12, adc13, adc14;
    int32_t loadCellRaw;
    float tcInternalTemp;
    float tcTemp1, tcTemp2, tcTemp3, tcTemp4;
    // fault flags is a bitfield [fault, open, gnd, vcc] from LSB to MSB for each tc reader, 1 meaning that fault is active
    uint8_t tcFaultFlags[4];
    uint16_t packetCRC;
} PropBoardSensorData;

#endif //ENGINECONTROLSYSTEM_PIUTILS_H
