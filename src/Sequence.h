//
// Created by kevin on 3/2/2022.
//

#ifndef BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#define BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
#include "ECSState.h"
#include <list>
#include <tuple>

class Sequence{
public:
    Sequence(std::list<std::tuple<ECSState, double>> seq){
        this->seq = seq;
    }
protected:
    std::list<std::tuple<ECSState, double>> seq;
};
#endif //BETTER_ENGINE_CONTROL_SOFTWARE_SEQUENCE_H
