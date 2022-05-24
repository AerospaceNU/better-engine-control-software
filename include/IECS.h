#ifndef ECS_H
#define ECS_H

#include "CommandData.h"

class IECS {
public:
    virtual void reportToBoundary();
    virtual void stepECS();
    virtual void acceptCommand(CommandData* commands);
};

#endif
