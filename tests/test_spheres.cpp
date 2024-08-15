//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("A ray intersects a sphere at two points") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 4.0);
    REQUIRE(xs[1].t == 6.0);
}

TEST_CASE("A ray intersects a sphere at a tangent") {
    const auto r = Ray {point(0,1,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 5.0);
    REQUIRE(xs[1].t == 5.0);
}

TEST_CASE("A ray misses a sphere") {
    const auto r = Ray {point(0,2,-5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersect(r);
    REQUIRE(xs.empty());
}

TEST_CASE("A ray originates inside a sphere") {
    const auto r = Ray {point(0,0,0), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == -1.0);
    REQUIRE(xs[1].t == 1.0);
}

TEST_CASE("A sphere is behind a ray") {
    const auto r = Ray {point(0,0,5), vector(0,0,1)};
    const auto s = Sphere {};
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == -6.0);
    REQUIRE(xs[1].t == -4.0);
}

TEST_CASE("A sphere's default transformtion") {
    const auto s = Sphere {};
    REQUIRE(s.transform == Matrix::Identity());
}

TEST_CASE("Changing a sphere's transformation") {
    const auto s = Sphere {};
    const auto t = translation(2,3,4);
    s.setTransform(t);
    REQUIRE(s.transform == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    const auto s = Sphere {};
    s.setTransform(scaling(2,2,2));
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 3);
    REQUIRE(xs[1].t == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    const auto s = Sphere {};
    s.setTransform(translation(5,0,0));
    const auto xs = s.intersect(r);
    REQUIRE(xs.empty());
}