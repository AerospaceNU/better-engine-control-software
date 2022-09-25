//
// Created by Cameron on 7/13/21.
//

#ifndef ENGINECONTROLSYSTEM_ECSTHREEWAYPIVALVE_H
#define ENGINECONTROLSYSTEM_ECSTHREEWAYPIVALVE_H

#include "IECSValve.h"
#include "wiringPi.h"

/**
 * This class is used to control the three way solenoid/valves by hiding
 * that we are actually controlling two digital outs
 */
class ECSThreeWayPiValve : public IECSValve {
public:
    ECSThreeWayPiValve(int topPinNumber, int botPinNumber);

    void setValveState(ECSValveState newState) override;
    ECSValveState getValveState() override;

private:
    int topPinNumber;
    int botPinNumber;
};


#endif //ENGINECONTROLSYSTEM_ECSTHREEWAYPIVALVE_H
