//
// Created by kevin on 10/24/2022.
//

#include "../catch.hpp"

#include "utils/ECSUtils.h"
#include <cmath>

TEST_CASE("filterDoubleNan", "[unit]") {
    REQUIRE_THAT(filterDoubleNan(1230.0), Catch::WithinRel(1230.0, 0.1));
    REQUIRE_THAT(filterDoubleNan(std::nan("")), Catch::WithinRel(0.0, 0.1));
}