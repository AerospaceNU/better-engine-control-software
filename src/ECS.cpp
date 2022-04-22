//
// Created by kevin on 2/23/2022.
//

#include "IBoundary.h"
#include "ECS.h"
#include <iostream>

ECS::ECS(IBoundary* boundary) {
    ECS::boundary = boundary;
}

#pragma clang diagnostic push
#pragma ide diagnostic ignored "EndlessLoop"
void ECS::run() {
    int counter = 0;
    while (true) {
        // std::cout << "We would read the sensors here!" << std::endl;
        // std::cout << this->boundary->readFromBoundary(counter)->sensor1Data << std::endl;
        // std::cout << "We would write data out of the ECS here!" << std::endl;

        counter++;
    }
}
#pragma clang diagnostic pop