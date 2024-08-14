//
// Created by sam on 8/12/24.
//

#include "test.h"

TEST_CASE("point() creates tuples with w = 1", "[point]") {
    const auto p = point(4, -4, 3);
    REQUIRE_TUPLES(p, Tuple {4,-4, 3, 1});
}

TEST_CASE("vector() creates tuples with w = 0", "[vector]") {
    const auto v = vector(4, -4, 3);
    REQUIRE_TUPLES(v, Tuple {4,-4, 3, 0});
}

TEST_CASE("Adding two tuples", "[add]") {
    const auto a1 = vector(3, -2, 5);
    const auto a2 = point(-2,3,1);
    REQUIRE_TUPLES(a1 + a2, Tuple {1,1,6,1});
}

TEST_CASE("Subtracting two tuples", "[subtract]") {
    const auto p1 = point(3, 2, 1);
    const auto p2 = point(5,6,7);
    REQUIRE_TUPLES(p1 - p2, vector(-2,-4,-6));
}

TEST_CASE("Subtracting a vector from a point", "[subtract]") {
    const auto p1 = point(3, 2, 1);
    const auto p2 = vector(5,6,7);
    REQUIRE_TUPLES(p1 - p2, point(-2,-4,-6));
}


TEST_CASE("Subtracting two vectors", "[subtract]") {
    const auto p1 = vector(3, 2, 1);
    const auto p2 = vector(5,6,7);
    REQUIRE_TUPLES(p1 - p2, vector(-2,-4,-6));
}

TEST_CASE("Subtracting a vector from the zero vector", "[subtract]") {
    const auto zero = vector();
    const auto v = vector(1,-2,3);
    REQUIRE_TUPLES(zero - v, vector(-1,2,-3));
}

TEST_CASE("Negating a tuple", "[negate]") {
    const auto a = Tuple { 1, -2, 3, -4 };
    REQUIRE_TUPLES(-a, Tuple {-1,2,-3,4});
}

TEST_CASE("Multiplying a tuple by a scalar", "[multiply]") {
    const auto a = Tuple { 1, -2, 3, -4 };
    REQUIRE_TUPLES(a * 3.5, Tuple {3.5,-7,10.5,-14});
}

TEST_CASE("Multiplying a tuple by a fraction", "[multiply]") {
    const auto a = Tuple { 1, -2, 3, -4 };
    REQUIRE_TUPLES(a * 0.5, Tuple {0.5,-1,1.5,-2});
}

TEST_CASE("Dividing a tuple by a scalar", "[divide]") {
    const auto a = Tuple { 1, -2, 3, -4 };
    REQUIRE_TUPLES(a / 2, Tuple {0.5,-1,1.5,-2});
}

TEST_CASE("Computing the magnitude of vector(1,0,0)", "[magnitude]") {
    const auto v = vector(1,0,0);
    REQUIRE(v.norm() == 1);
}

TEST_CASE("Computing the magnitude of vector(0,1,0)", "[norm]") {
    const auto v = vector(0,1,0);
    REQUIRE(v.norm() == 1);
}

TEST_CASE("Computing the magnitude of vector(0,0,1)", "[norm]") {
    const auto v = vector(0,0,1);
    REQUIRE(v.norm() == 1);
}

TEST_CASE("Computing the magnitude of vector(1,2,3)", "[norm]") {
    const auto v = vector(1,2,3);
    REQUIRE(v.norm() == std::sqrt(14));
}

TEST_CASE("Computing the magnitude of vector(-1,-2,-3)", "[norm]") {
    const auto v = vector(-1,-2,-3);
    REQUIRE(v.norm() == std::sqrt(14));
}


TEST_CASE("Normalizing vector(4,0,0) gives vector(1,0,0)", "[normalizing]") {
    const auto v = vector(4,0,0);
    REQUIRE_TUPLES(v.normalize(), vector(1,0,0));
}

TEST_CASE("Normalizing vector(1,2,3)", "[normalizing]") {
    const auto v = vector(1,2,3);
    REQUIRE_TUPLES(v.normalize(), vector(1/ std::sqrt(14),2/ std::sqrt(14),3/ std::sqrt(14)));
}

TEST_CASE("norm of a normalised vector", "[normalizing]") {
    const auto v = vector(1,2,3);
    REQUIRE(v.normalize().norm() == 1);
}