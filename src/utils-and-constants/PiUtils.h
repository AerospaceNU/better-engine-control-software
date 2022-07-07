//
// Created by Cameron on 5/13/21.
//

#ifndef ENGINECONTROLSYSTEM_PIUTILS_H
#define ENGINECONTROLSYSTEM_PIUTILS_H

#include <cstdint>

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



#endif //ENGINECONTROLSYSTEM_PIUTILS_H
