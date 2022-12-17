//
// Created by David.L on 10/19/22.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H

#include "IECSValve.h"

/**
 * Implementation of a simulated IECSValve that will correctly
 * store and change its state
 *
 * Useful for unit testing
 */
class FakeECSValve : public IECSValve {
public:
    explicit FakeECSValve(ECSValveState initialState);

    /**
     * Mutates stored state to new state
     * @param newState state to store
     * @throws EffectorException if given ECSValveState::INVALID
     */
    void setValveState(ECSValveState newState) override;

    /**
     * Returns stored state
     * @return currentSTATE
     */
    ECSValveState getValveState() override;

private:
    ECSValveState currentSTATE;
};

#endif //BETTER_ENGINE_CONTROL_SOFTWARE_FAKEIECSVALVE_H

