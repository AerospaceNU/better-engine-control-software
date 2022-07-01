//
// Created by Cameron Bracco on 1/29/2021.
//

#ifndef ENGINECONTROLSYSTEM_IECSVALVE_H
#define ENGINECONTROLSYSTEM_IECSVALVE_H

#include "utils-and-constants/ECSUtils.h"

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
     * @throws exception [type to be specified later] valve fails to write
     */
    virtual void setValveState(ECSValveState newState) = 0;
};

#endif //ENGINECONTROLSYSTEM_IECSVALVE_H
