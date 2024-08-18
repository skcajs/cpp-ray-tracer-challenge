//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("Creating and querying a ray") {
    const auto origin = point(1,2,3);
    const auto direction = vector(4,5,6);
    const auto r = Ray  { origin, direction };

    COMPARE_TUPLES(r.origin, origin);
    COMPARE_TUPLES(r.direction, direction);
}

TEST_CASE("Computing a point from a distance") {
    const auto r = Ray  { point(2,3,4), vector(1,0,0) };

    COMPARE_TUPLES(r.position(0), point(2,3,4));
    COMPARE_TUPLES(r.position(1), point(3,3,4));
    COMPARE_TUPLES(r.position(-1), point(1,3,4));
    COMPARE_TUPLES(r.position(2.5), point(4.5,3,4));
}

TEST_CASE("Translating a ray") {
    const auto r = Ray {point(1,2,3), vector(0,1,0)};
    const auto m = translation(3,4,5);
    const auto r2 = r.transform(m);

    REQUIRE(r2.origin == point(4,6,8));
    COMPARE_TUPLES(r2.direction, vector(0,1,0));
}

TEST_CASE("Scaling a ray") {
    const auto r = Ray {point(1,2,3), vector(0,1,0)};
    const auto m = scaling(2,3,4);
    const auto r2 = r.transform(m);

    COMPARE_TUPLES(r2.origin, point(2,6,12));
    COMPARE_TUPLES(r2.direction, vector(0,3,0));
}