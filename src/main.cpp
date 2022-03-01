//
// Created by Matthew Coughlin on 2/23/22.
//
#include "ECS.h"
#include "IBoundary.h"
#include "FakeBoundary.h"

int main() {
    IBoundary* boundary = new FakeBoundary();
    ECS* ecs = new ECS(boundary);
    ecs->run();

    return 0;
}