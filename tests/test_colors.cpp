//
// Created by sam on 8/13/24.
//

#include "test.h"

inline void compareColors(const Color &r, const Color &l, const double EPSILON = 1e-5) {
    REQUIRE(std::fabs(r.r - l.r) < EPSILON);
    REQUIRE(std::fabs(r.g - l.g) < EPSILON);
    REQUIRE(std::fabs(r.b - l.b) < EPSILON);
    REQUIRE(std::fabs(r.a - l.a) < EPSILON);
}

TEST_CASE("Adding colors", "[add]") {
    const auto c1 = Color { 0.9, 0.6, 0.75 };
    const auto c2 = Color { 0.7, 0.1, 0.25 };
    compareColors(c1 + c2, Color {1.6,0.7, 1.0});
}

TEST_CASE("Subtract colors", "[subtract]") {
    const auto c1 = Color { 0.9, 0.6, 0.75 };
    const auto c2 = Color { 0.7, 0.1, 0.25 };
    compareColors(c1 - c2, Color {0.2, 0.5, 0.5});
}

TEST_CASE("Multiplying a color by a scalar", "[multiply]") {
    const auto c1 = Color { 0.2, 0.3, 0.4 };
    compareColors(c1 * 2, Color {0.4, 0.6, 0.8});
}

TEST_CASE("Multiplying colors", "[multiply]") {
    const auto c1 = Color { 1, 0.2, 0.4 };
    const auto c2 = Color { 0.9, 1, 0.1 };
    compareColors(c1 * c2, Color {0.9, 0.2, 0.04});
}
