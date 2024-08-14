//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("Creating and querying a ray") {
    const auto origin = point(1,2,3);
    const auto direction = vector(4,5,6);
    const auto r = Ray  { origin, direction };

    REQUIRE_TUPLES(r.origin, origin);
    REQUIRE_TUPLES(r.direction, direction);
}

TEST_CASE("Computing a point from a distance") {
    const auto r = Ray  { point(2,3,4), vector(1,0,0) };

    REQUIRE_TUPLES(r.position(0), point(2,3,4));
    REQUIRE_TUPLES(r.position(1), point(3,3,4));
    REQUIRE_TUPLES(r.position(-1), point(1,3,4));
    REQUIRE_TUPLES(r.position(2.5), point(4.5,3,4));
}