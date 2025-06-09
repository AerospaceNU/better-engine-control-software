//
// Created by kevin on 12/7/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKECOMMBOUNDARY_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKECOMMBOUNDARY_H

#include "ICommBoundary.h"
#include <etl/vector.h> 

/**
 * Mock impl of ICommBoundary
 *
 * Useful for unit testing
 */
class FakeCommBoundary: public ICommBoundary{
public:
    void reportState(ECSState& curState) override;
    void reportRedlines(etl::vector<RedlineResponsePacket, 45>) override;
    void reportSensorData(SensorData data, bool isCalibrated) override;
    void reportMessage(std::string msg) override;

    bool stateReported = false;
    bool redlinesReported = false;
    bool sensorDataReported = false;
    bool messageReported = false;
};


#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKECOMMBOUNDARY_H
