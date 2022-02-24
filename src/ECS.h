//
// Created by kevin on 2/23/2022.
//

#pragma once
#include "Boundary.h"

class ECS {

public:
    ECS(Boundary* boundary);
    void run();

private:
    Boundary* boundary;
};


