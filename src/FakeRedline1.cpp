//
// Created by kevin on 3/28/2022.
//

#include "FakeRedline1.h"

//FakeRedline1::FakeRedline1(std::string n, int llimit, int ulimit):
//    Redline(n, llimit, ulimit)
//{
//}

bool FakeRedline1::testCondition(SensorData* data) {
    return data->sensor1Data < upperLimit and data->sensor2Data > lowerLimit;
}