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

TEST_CASE("Translating a ray") {
    const auto r = Ray {point(1,2,3), vector(0,1,0)};
    const auto m = translation(3,4,5);
    const auto r2 = r.transform(m);
    const auto origin = r2.origin;
    const auto direction = r2.direction;
    std::cout << "Transformed origin: " << origin.x << ", " << origin.y << ", " << origin.z << ", " << origin.w << std::endl;
    std::cout << "Transformed direction: " << direction.x << ", " << direction.y << ", " << direction.z << ", " << direction.w << std::endl;
    REQUIRE(origin == point(4,6,8));
    REQUIRE_TUPLES(r2.direction, vector(0,1,0));
}