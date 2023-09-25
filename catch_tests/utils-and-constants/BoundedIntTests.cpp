//
// Created by kevin on 8/24/2022.
//

#include "../catch.hpp"
#include "utils/BoundedInt.h"

TEST_CASE("BoundedInt", "[unit]"){
    BoundedInt<0, 100> boundedInt;

    // TODO: I WISH we could actually test that these static_asserts fail
    // [[maybe_unused]] BoundedInt<0, 0> bInt2;
    // [[maybe_unused]] BoundedInt<0, -1> bInt3;

    SECTION("Testing middle of road input"){
        boundedInt = BoundedInt<0, 100>(50);
        REQUIRE(boundedInt == 50);
    }

    SECTION("Testing upper bound"){
        boundedInt = BoundedInt<0, 100>(100);
        REQUIRE(boundedInt == 100);

        boundedInt = BoundedInt<0, 100>(101);
        REQUIRE(boundedInt == 100);

        boundedInt = BoundedInt<0, 100>(101000);
        REQUIRE(boundedInt == 100);
    }

    SECTION("Testing lower bound"){
        boundedInt = BoundedInt<0, 100>(0);
        REQUIRE(boundedInt == 0);

        boundedInt = BoundedInt<0, 100>(-1);
        REQUIRE(boundedInt == 0);

        boundedInt = BoundedInt<0, 100>(-10000000);
        REQUIRE(boundedInt == 0);
    }
}
