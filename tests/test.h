//
// Created by sam on 8/13/24.
//

#ifndef TESTS_H
#define TESTS_H

#define CATCH_CONFIG_MAIN

#include <catch2/catch_all.hpp>

#include <cmath>
#include <iostream>

#include "../src/Tuple.h"
#include "../src/Color.h"
#include "../src/Matrix.h"
#include "../src/Canvas.h"
#include "../src/Transformations.h"
#include "../src/Ray.h"
#include "../src/Sphere.h"
#include "../src/Intersection.h"
#include "../src/Intersections.h"
#include "../src/Light.h"
#include "../src/Material.h"
#include "../src/World.h"



inline void COMPARE_TUPLES(const Tuple &r, const Tuple &l, const double EPSILON = 1e-5) {
    auto is_zero = [EPSILON](const double value) {
        return std::fabs(value) < EPSILON;
    };

    if (is_zero(l.x-r.x)) {
        REQUIRE(true);
    } else {
        REQUIRE(l.x == Catch::Approx(r.x).epsilon(EPSILON));
    }
    if (is_zero(l.y-r.y)) {
        REQUIRE(true);
    } else {
        REQUIRE(l.y == Catch::Approx(r.y).epsilon(EPSILON));
    }
    if (is_zero(l.z-r.z)) {
        REQUIRE(true);
    } else {
        REQUIRE(l.z == Catch::Approx(r.z).epsilon(EPSILON));
    }
    if (is_zero(l.w-r.w)) {
        REQUIRE(true);
    } else {
        REQUIRE(l.w == Catch::Approx(r.w).epsilon(EPSILON));
    }
}

inline void COMPARE_COLORS(const Color &l, const Color &r, const double EPSILON = 1e-4) {
    REQUIRE(l.r == Catch::Approx(r.r).epsilon(EPSILON));
    REQUIRE(l.g == Catch::Approx(r.g).epsilon(EPSILON));
    REQUIRE(l.b == Catch::Approx(r.b).epsilon(EPSILON));
    REQUIRE(l.a == Catch::Approx(r.a).epsilon(EPSILON));
}

inline void COMPARE_MATRICES(const Matrix &r, const Matrix &l) {
    const auto shape = l.Size();

    for (int i = 0; i < shape; ++i) {
        for (int j = 0; j < shape; ++j) {
            REQUIRE(r.element(i,j) == Catch::Approx(l.element(i,j)).epsilon(1e-3));
        }
    }
}

inline void COMPARE_MATERIALS(const Material &l, const Material &r) {
    REQUIRE(l.ambient == r.ambient);
    COMPARE_COLORS(l.color, r.color);
    REQUIRE(l.diffuse == r.diffuse);
    REQUIRE(l.specular == r.specular);
    REQUIRE(l.shininess == r.shininess);
}

#endif //TESTS_H
