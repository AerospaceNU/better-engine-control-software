//
// Created by Matthew Coughlin on 2/23/22.
//
#include "ECS.h"
#include "Boundary.h"

int main() {
    Boundary* boundary = new FakeBoundary();
    ECS* ecs = new ECS(boundary);
    ecs->run();

    return 0;
}