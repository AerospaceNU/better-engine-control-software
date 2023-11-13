//
// Created by kevin on 12/7/2022.
//

#include "FakeCommBoundary.h"
#include <etl/vector.h>

void FakeCommBoundary::reportState([[maybe_unused]] ECSState &curState) {
    this->stateReported = true;
}

void FakeCommBoundary::reportRedlines([[maybe_unused]] etl::vector<RedlineResponsePacket, 45> redlineReports) {
    this->redlinesReported = true;
}

void FakeCommBoundary::reportSensorData([[maybe_unused]] SensorData data, [[maybe_unused]] bool isCalibrated) {
    this->sensorDataReported = true;
}

void FakeCommBoundary::reportMessage([[maybe_unused]] std::string msg) {
    this->messageReported = true;
}
