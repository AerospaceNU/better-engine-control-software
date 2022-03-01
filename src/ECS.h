//
// Created by kevin on 2/23/2022.
//

#pragma once
#include "IBoundary.h"

class ECS {

public:
    ECS(IBoundary* boundary);
    void run();

private:
    IBoundary* boundary;
};


