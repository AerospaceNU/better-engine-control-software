//
// Created by Matthew Coughlin on 2/23/22.
//
#include "IECS.h"
#include "PhysicalBoundary.h"
#include "FakeBoundary.h"

#include "SensorData.h"
#include "WatchDog.h"

int main() {
//    PhysicalBoundary* boundary = new FakeBoundary();
//    IECS* ecs = new IECS(boundary);
//    ecs->run();

    WatchDog* w = new WatchDog();

    w->stepRedlines(new SensorData());
    return 0;
}