//
// Created by Cameron Bracco on 1/29/2021.
//

#ifndef ENGINECONTROLSYSTEM_IECSVALVE_H
#define ENGINECONTROLSYSTEM_ECSVALVE_H

#include "utils-and-constants/ECSUtils.h"

class IECSValve {
public:
    virtual ECSValveState getValveState() = 0;
    virtual void setValveState(ECSValveState newState) = 0;
};

#endif //ENGINECONTROLSYSTEM_IECSVALVE_H
