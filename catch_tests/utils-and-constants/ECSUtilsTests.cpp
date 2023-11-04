//
// Created by kevin on 10/24/2022.
//

#include "../catch.hpp"

#include "utils/ECSUtils.h"
#include <cmath>

#include <chrono>
#include <thread>

namespace {
    struct Foo {
        explicit Foo(int a_) :
                a(a_) {};

        int a;
    };
}

TEST_CASE("getTimeStamp monotonic time") {
    auto prevTime = getTimeStamp();

    for (int i = 0; i < 10; i++){
        // std::this_thread::sleep_for(std::chrono::milliseconds(10));
        auto curTime = getTimeStamp();

        assert(prevTime <= curTime);
        prevTime = curTime;
    }
}

TEST_CASE("make_vector_unique", "[unit]") {
    std::vector<std::unique_ptr<Foo>> result = make_vector_unique<Foo>(std::make_unique<Foo>(21312),
                                                                     std::make_unique<Foo>(45342),
                                                                     std::make_unique<Foo>(7654),
                                                                     std::make_unique<Foo>(345),
                                                                     std::make_unique<Foo>(9));
    REQUIRE(result.size() == 5);

    REQUIRE(result[0]->a == 21312);
    REQUIRE(result[1]->a == 45342);
    REQUIRE(result[2]->a == 7654);
    REQUIRE(result[3]->a == 345);
    REQUIRE(result[4]->a == 9);
}

TEST_CASE("filterDoubleNan", "[unit]") {
    REQUIRE_THAT(filterDoubleNan(1230.0), Catch::WithinRel(1230.0, 0.1));
    REQUIRE_THAT(filterDoubleNan(std::nan("")), Catch::WithinRel(0.0, 0.1));
}
