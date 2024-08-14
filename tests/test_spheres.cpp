//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("A ray intersects a sphere at two points") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersects(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0] == 4.0);
    REQUIRE(xs[1] == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    const auto r = Ray {point(0,1,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersects(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0] == 5.0);
    REQUIRE(xs[1] == 5.0);
}

TEST_CASE("A ray misses a sphere") {
    const auto r = Ray {point(0,2,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersects(r);
    REQUIRE(xs.empty());
}

TEST_CASE("A ray originates inside a sphere") {
    const auto r = Ray {point(0,0,0), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersects(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0] == -1.0);
    REQUIRE(xs[1] == 1.0);
}

TEST_CASE("A sphere is behind a ray") {
    const auto r = Ray {point(0,0,5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersects(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0] == -6.0);
    REQUIRE(xs[1] == -4.0);
}
