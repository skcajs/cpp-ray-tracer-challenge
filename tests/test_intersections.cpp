//
// Created by sam on 8/14/24.
//

#include "test.h"

TEST_CASE("An intersection encapsulates t and object") {
    const auto s = Sphere();
    const auto i = Intersection(3.5, s);
    REQUIRE(i.t == 3.5);
    REQUIRE(i.object == s);
}

TEST_CASE("Aggregating intersections") {
    const auto s = Sphere{};
    const auto i1 = Intersection(1, s);
    const auto i2 = Intersection(2, s);
    const auto xs2 = Intersections {};
    const auto xs = Intersections {i1, i2};
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 1);
    REQUIRE(xs[1].t == 2);
}

TEST_CASE("Intersect sets the object on the intersection") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    const auto s = Sphere{};
    const auto xs = s.intersects(r);
    REQUIRE(xs.size() == 2);
}