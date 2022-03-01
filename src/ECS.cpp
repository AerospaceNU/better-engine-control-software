//
// Created by kevin on 2/23/2022.
//

#include "ECS.h"
#include <iostream>

ECS::ECS(Boundary* boundary) {
    ECS::boundary = boundary;
}

void ECS::run() {
    while (true) {
        std::cout << "We would read the sensors here!" << std::endl;
        std::cout << "We would write data out of the ECS here!" << std::endl;
    }
}