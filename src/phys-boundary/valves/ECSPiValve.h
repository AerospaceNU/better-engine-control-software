//
// Created by Cameron on 5/13/21.
//

#ifndef ENGINECONTROLSYSTEM_ECSPIVALVE_H
#define ENGINECONTROLSYSTEM_ECSPIVALVE_H

#include "IECSValve.h"

/**
 * Basic valve used on Raspberry Pi
 */
class ECSPiValve : public IECSValve {
public:
    ECSPiValve(ECSValveState initialState, int pNumber);

    void setValveState(ECSValveState newState) override;
    ECSValveState getValveState() override;

private:
    ECSValveState defaultState;
    int pinNumber;
};


#endif //ENGINECONTROLSYSTEM_ECSPIVALVE_H
