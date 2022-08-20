//
// Created by Cameron Bracco on 1/29/2021.
//

#ifndef ENGINECONTROLSYSTEM_IECSVALVE_H
#define ENGINECONTROLSYSTEM_IECSVALVE_H

#include "utils/ECSUtils.h"
#include "EffectorException.h"

class IECSValve {
public:
    /**
     * Gets the current valve state
     * @return current valve state
     */
    virtual ECSValveState getValveState() = 0;

    /**
     * Sets this valve to the given state
     * @param newState state the valve should be in after method
     * @throws EffectorException valve fails to write
     */
    virtual void setValveState(ECSValveState newState) = 0;

    /**
     * Destructor, making it virtual to avoid undefined behavior
     */
    virtual ~IECSValve() = default;
};

#endif //ENGINECONTROLSYSTEM_IECSVALVE_H
