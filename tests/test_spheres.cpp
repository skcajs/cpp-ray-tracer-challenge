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
    auto s = Sphere {};
    const auto t = translation(2,3,4);
    s.setTransform(t);
    REQUIRE(s.transform == t);
}

TEST_CASE("Intersecting a scaled sphere with a ray") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    auto s = Sphere {};
    s.setTransform(scaling(2,2,2));
    const auto xs = s.intersect(r);
    REQUIRE(xs.size() == 2);
    REQUIRE(xs[0].t == 3);
    REQUIRE(xs[1].t == 7);
}

TEST_CASE("Intersecting a translated sphere with a ray") {
    const auto r = Ray {point(0,0,-5), vector(0,0,1)};
    auto s = Sphere {};
    s.setTransform(translation(5,0,0));
    const auto xs = s.intersect(r);
    REQUIRE(xs.empty());
}

TEST_CASE("The normal on a sphere at a point on the x axis") {
    const auto s = Sphere {};
    const auto n = s.normalAt(point(1, 0, 0));
    REQUIRE_TUPLES(n, vector(1,0,0));
}

TEST_CASE("The normal on a sphere at a point on the y axis") {
    const auto s = Sphere {};
    const auto n = s.normalAt(point(0, 1, 0));
    REQUIRE_TUPLES(n, vector(0,1,0));
}

TEST_CASE("The normal on a sphere at a point on the z axis") {
    const auto s = Sphere {};
    const auto n = s.normalAt(point(0, 0, 1));
    REQUIRE_TUPLES(n, vector(0,0,1));
}

TEST_CASE("The normal on a sphere at a nonaxial point") {
    const auto root = std::sqrt(3)/3.0;
    const auto s = Sphere {};
    const auto n = s.normalAt(point(root, root, root));
    REQUIRE_TUPLES(n, vector(root,root,root));
}

TEST_CASE("The normal is a normalized vector") {
    constexpr auto root = std::sqrt(3)/3.0;
    const auto s = Sphere {};
    const auto n = s.normalAt(point(root, root, root));
    REQUIRE_TUPLES(n, vector(root,root,root).normalize());
}

TEST_CASE("Computing the normal on a translated sphere") {
    constexpr auto a = 0.70711;
    auto s = Sphere {};
    s.setTransform(translation(0,1,0));
    const auto n = s.normalAt(point(0, 1+a, -a));
    REQUIRE_TUPLES(n, vector(0,a,-a));
}

TEST_CASE("Computing the normal on a transformed sphere") {
    constexpr auto root = std::sqrt(2)/2;
    auto s = Sphere {};
    s.setTransform(scaling(1,0.5,1) * rotationZ(M_PI/5));
    const auto n = s.normalAt(point(0, root, -root));
    REQUIRE_TUPLES(n, vector(0,0.97014,-0.24254));
}