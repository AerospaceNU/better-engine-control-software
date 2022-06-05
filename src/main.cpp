//
// Created by Matthew Coughlin on 2/23/22.
//
#include "generic/IECS.h"
#include "generic/IPhysicalBoundary.h"
#include "FakeBoundary.h"
#include "utils-and-constants/HorizontalECSRedlines.h"

#include "SensorData.h"
#include "WatchDog.h"

int main() {
//    IPhysicalBoundary* boundary = new FakeBoundary();
//    IECS* ecs = new IECS(boundary);
//    ecs->run();

    WatchDog w(ONLINE_SAFE_D);

    w.stepRedlines(new SensorData());
    return 0;
}