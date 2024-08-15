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

inline void REQUIRE_TUPLES(const Tuple &r, const Tuple &l, const double EPSILON = 1e-5) {
    REQUIRE(std::fabs(r.x - l.x) < EPSILON);
    REQUIRE(std::fabs(r.y - l.y) < EPSILON);
    REQUIRE(std::fabs(r.z - l.z) < EPSILON);
    REQUIRE(std::fabs(r.w - l.w) < EPSILON);
}

inline void REQUIRE_COLORS(const Color &r, const Color &l, const double EPSILON = 1e-5) {
    REQUIRE(std::fabs(r.r - l.r) < EPSILON);
    REQUIRE(std::fabs(r.g - l.g) < EPSILON);
    REQUIRE(std::fabs(r.b - l.b) < EPSILON);
    REQUIRE(std::fabs(r.a - l.a) < EPSILON);
}

inline void REQUIRE_MATRICES(const Matrix &r, const Matrix &l) {
    const auto shape = l.Size();

    for (int i = 0; i < shape; ++i) {
        for (int j = 0; j < shape; ++j) {
            REQUIRE(r.element(i,j) == Catch::Approx(l.element(i,j)));
        }
    }
}

#endif //TESTS_H
