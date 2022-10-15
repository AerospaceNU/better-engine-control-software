//
// Created by kevin on 9/20/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H

#include "PiUtils.h"
#include "SerialPortSource.h"

using ADCPacketSource = SerialPortSource<AdcBreakoutSensorData>;

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_ADCPACKETSOURCE_H
