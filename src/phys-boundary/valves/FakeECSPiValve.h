//
// Created by David.L on 10/19/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H

#include "IECSValve.h"

class FakeECSPiValve : public IECSValve {
public:
    FakeECSPiValve(ECSValveState initialState);

    void setValveState(ECSValveState newState) override;
    ECSValveState getValveState() override; //outputs the currentSTATE

private:
    ECSValveState currentSTATE;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H

