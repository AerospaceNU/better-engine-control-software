//
// Created by kevin on 2/23/2022.
//

#ifndef ECS_H
#define ECS_H
#include "IBoundary.h"

class ECS {

public:
    ECS(IBoundary* boundary);
    void run();

private:
    IBoundary* boundary;
};

#endif
