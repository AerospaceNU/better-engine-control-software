//
// Created by kevin on 10/12/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H

#include "PiUtils.h"
#include "SerialPortSource.h"

/**
 * Quick typedef so we don't have to say
 * "SerialPortSource<PropBoardSensorData>" every time
 */
using PropBoardSource = SerialPortSource<PropBoardSensorData>;


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_PROPBOARDSOURCE_H
