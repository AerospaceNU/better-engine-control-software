#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H

#include "SensorData.h"
#include <vector>

/**
 * Takes a vector containing SensorDatas and creates a SensorData with the average of 
 * its numeric fields
 * Valves and fault flags are set to the values of the last SensorData in the vector
 * If the data is empty then return default SensorData
 * @param data takes in a vector containing SensorDatas
 * @return A SensorData
 */
SensorData averageData(std::vector<SensorData> data);

/**
 * Takes a vector that contains SensorDatas and creates a SensorData with the medians of 
 * its numeric fields
 * Valves and fault flags are set to the values of the last SensorData in the vector
 * In the case of empty data, return the  default empty SensorData
 * @param data takes in a vector that contains SensorDatas
 * @return A SensorData
 */
SensorData medianData(std::vector<SensorData> data);


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SENSORDATAUTILS_H
