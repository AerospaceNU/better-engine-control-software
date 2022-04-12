//
// Created by kevin on 3/28/2022.
//

#include "FakeRedline1.h"

bool FakeRedline1::testCondition(SensorData data) {
    return data.sensor1Data < upperLimit and data.sensor2Data > lowerLimit
}