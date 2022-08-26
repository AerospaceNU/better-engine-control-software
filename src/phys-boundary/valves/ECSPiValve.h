//
// Created by Cameron on 5/13/21.
//

#ifndef ENGINECONTROLSYSTEM_ECSPIVALVE_H
#define ENGINECONTROLSYSTEM_ECSPIVALVE_H

#include "IECSValve.h"
#include "wiringPi.h"

class ECSPiValve : public IECSValve {
public:
    ECSPiValve(ECSValveState initialState, int pNumber);

    void setValveState(ECSValveState newState) override;
    ECSValveState getValveState() override;
protected:
    int pinNumber;
    ECSValveState defaultState;
};


#endif //ENGINECONTROLSYSTEM_ECSPIVALVE_H
