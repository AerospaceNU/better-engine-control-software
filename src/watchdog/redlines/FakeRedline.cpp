//
// Created by kevin on 12/8/2022.
//

#include "FakeRedline.h"
#include <utility>

FakeRedline::FakeRedline(std::string name_, ECSRedLineResponse result):
    name(std::move(name_)),
    alwaysResponse(result)
{}

std::string FakeRedline::getName() const {
    return this->name;
}

ECSRedLineResponse FakeRedline::testCondition([[maybe_unused]] const SensorData &data) {
    return this->alwaysResponse;
}

std::unique_ptr<IRedline> FakeRedline::clone() {
    return std::make_unique<FakeRedline>(*this);
}
