//
// Created by kevin on 4/11/2022.
//
#include "IntWithinRedline.h"
#include <stdexcept>
#include <utility>


IntWithinRedline::IntWithinRedline(std::string name_, std::function<int(SensorData&)>& sFunct, int lBound, int uBound,
                                   ECSRedLineResponse res):
        name(std::move(name_)),
        selector(sFunct),
        lowerBound(lBound),
        upperBound(uBound),
        response(res)
{
    if (lBound >= uBound){
        throw std::invalid_argument("Lower bound cannot be greater than upper bound");
    }
}

std::string IntWithinRedline::getName() const{
    return this->name;
}

ECSRedLineResponse IntWithinRedline::testCondition(SensorData& data) {
    int testNum = this->selector(data);

    if ((this->lowerBound <= testNum) && (testNum <= this->upperBound)) {
        return ECSRedLineResponse::SAFE;
    }

    return this->response;
}


std::unique_ptr<IRedline> IntWithinRedline::clone() {
    return std::make_unique<IntWithinRedline>(*this);
}

std::unique_ptr<IntWithinRedline> RedlineFactory(std::string name,
                                                 std::function<int(SensorData&)>& sFunct,
                                                 int lBound,
                                                 int uBound,
                                                 ECSRedLineResponse r) {
    return std::make_unique<IntWithinRedline>(std::move(name), sFunct, lBound, uBound, r);
}