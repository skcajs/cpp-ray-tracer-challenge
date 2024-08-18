//
// Created by sam on 8/18/24.
//

#include "test.h"


TEST_CASE("Creating a world") {
    const auto w = World {};
    REQUIRE(w.objects.empty());
    REQUIRE_FALSE(w.light.has_value());
}

TEST_CASE("The default world") {
    const auto light = pointLight(point(-10, 10, -10), color(1,1,1));

    Sphere s1 {};
    s1.material.color = color(0.8,1.0,0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    Sphere s2 {};
    s2.transform = scaling(0.5,0.5,0.5);

    std::vector<Sphere> objects;
    objects.emplace_back(s1);
    objects.emplace_back(s2);

    const auto w = defaultWorld();
    REQUIRE(w.objects[0] == s1);
    REQUIRE(w.objects[1] == s2);
    REQUIRE(w.light == light);
}

TEST_CASE("Intersect a world with a ray") {
    const auto w = defaultWorld();
    const auto r = Ray { point(0,0,-5), vector(0,0,1) };
    const auto xs = w.intersectWorld(r);
    REQUIRE(xs.size() == 4);
    REQUIRE(xs[0].t == 4);
    REQUIRE(xs[1].t == 4.5);
    REQUIRE(xs[2].t == 5.5);
    REQUIRE(xs[3].t == 6);
}

TEST_CASE("Shading an intersection") {
    const auto w = defaultWorld();
    const auto r = Ray { point(0,0, -5), vector(0,0,1)};
    const auto shape = w.objects[0];
    const auto i = Intersection(4, &shape);
    const auto comps = i.prepare_computations(r);
    const auto c = w.shadeHit(comps);
    COMPARE_COLORS(c, color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("Shading an intersection from the inside") {
    auto w = defaultWorld();
    w.light = pointLight(point(0, 0.25, 0), color(1, 1, 1));
    const auto r = Ray { point(0,0, 0), vector(0,0,1)};
    const auto shape = w.objects[1];
    const auto i = Intersection(0.5, &shape);
    const auto comps = i.prepare_computations(r);
    const auto c = w.shadeHit(comps);
    COMPARE_COLORS(c, color(0.90498, 0.90498, 0.90498));
}

TEST_CASE("The color when a ray misses") {
    const auto w = defaultWorld();
    const auto r = Ray { point(0,0, -5), vector(0,1,0)};
    const auto c = w.colorAt(r);
    COMPARE_COLORS(c, color(0, 0, 0));
}

TEST_CASE("The color when a ray hits") {
    const auto w = defaultWorld();
    const auto r = Ray { point(0,0, -5), vector(0,0,1)};
    const auto c = w.colorAt(r);
    COMPARE_COLORS(c, color(0.38066, 0.47583, 0.2855));
}

TEST_CASE("The color with an intersection behind the ray") {
    auto w = defaultWorld();
    auto &outer = w.objects[0];
    outer.material.ambient = 1;
    auto &inner = w.objects[1];
    inner.material.ambient = 1;
    const auto r = Ray { point(0,0, 0.75), vector(0,0,-1)};
    const auto c = w.colorAt(r);
    COMPARE_COLORS(c, inner.material.color);
}