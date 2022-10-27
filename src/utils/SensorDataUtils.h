#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H

#include "SensorData.h"
#include <vector>

/**
 * Takes a vector containing SensorDatas and perform an average on it
 * If the data is empty then return default SensorData
 * @param data takes in a vector containing SensorDatas
 * @return A SensorData
 */

SensorData averageData(std::vector<SensorData> data);

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H
