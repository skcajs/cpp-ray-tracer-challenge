//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("Multiplying by a translation matrix") {
    const auto transform = translation(5, -3, 2);
    const auto p = point(-3,4,5);
    COMPARE_TUPLES(transform * p, point (2,1,7));
}

TEST_CASE("Multiplying by the inverse of a translation matrix") {
    const auto transform = translation(5, -3, 2);
    const auto inv = transform.inverse();
    const auto p = point(-3,4,5);
    const auto r = inv * p;
    COMPARE_TUPLES(r, point (-8,7,3));
}

TEST_CASE("Translation does not affect vectors") {
    const auto transform = translation(5, -3, 2);
    const auto v = vector(-3,4,5);
    COMPARE_TUPLES(transform * v, v);
}

TEST_CASE("A scaling matrix applied to a point") {
    const auto transform = scaling(2, 3, 4);
    const auto p = point(-4,6,8);
    COMPARE_TUPLES(transform * p, point(-8,18,32));
}

TEST_CASE("A scaling matrix applied to a vector") {
    const auto transform = scaling(2, 3, 4);
    const auto v = point(-4,6,8);
    COMPARE_TUPLES(transform * v, point(-8,18,32));
}

TEST_CASE("Multiplying by the inverse of a scaling matrix") {
    const auto transform = scaling(2, 3, 4);
    const auto inv = transform.inverse();
    const auto v = vector(-4,6,8);
    COMPARE_TUPLES(inv * v, vector(-2,2,2));
}

TEST_CASE("Reflection is scaling by a negative value") {
    const auto transform = scaling(-1, 1, 1);
    const auto p = vector(2,3,4);
    COMPARE_TUPLES(transform * p, vector(-2,3,4));
}

TEST_CASE("Rotating around the x axis") {
    const auto p = point(0,1,0);
    const auto halfQuarter = rotationX(M_PI/4);
    const auto fullQuarter = rotationX(M_PI/2);
    COMPARE_TUPLES(halfQuarter * p, point(0,std::sqrt(2)/2,std::sqrt(2)/2));
    COMPARE_TUPLES(fullQuarter * p, point(0,0,1));
}

TEST_CASE("The inverse of the x-rotation matrix rotates in the opposite direction") {
    const auto p = point(0,1,0);
    const auto halfQuarter = rotationX(M_PI/4);
    const auto inv = halfQuarter.inverse();
    COMPARE_TUPLES(inv * p, point(0,std::sqrt(2)/2,-std::sqrt(2)/2));
}

TEST_CASE("Rotating a point around the y axis") {
    const auto p = point(0, 0, 1);
    const auto halfQuarter = rotationY(M_PI / 4);
    const auto fullQuarter = rotationY(M_PI / 2);
    COMPARE_TUPLES(halfQuarter * p, point(std::sqrt(2) / 2, 0, std::sqrt(2) / 2));
    COMPARE_TUPLES(fullQuarter * p, point(1, 0, 0));
}

TEST_CASE("Rotating a point around the z axis") {
    const auto p = point(0, 1, 0);
    const auto halfQuarter = rotationZ(M_PI / 4);
    const auto fullQuarter = rotationZ(M_PI / 2);

    COMPARE_TUPLES(halfQuarter * p, point(-std::sqrt(2) / 2, std::sqrt(2) / 2, 0));
    COMPARE_TUPLES(fullQuarter * p, point(-1, 0, 0));
}

TEST_CASE("A shearing transformation moves x in proportion to y") {
    const auto transform = shearing(1, 0, 0, 0, 0, 0);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(5, 3, 4));
}

TEST_CASE("A shearing transformation moves x in proportion to z") {
    const auto transform = shearing(0, 1, 0, 0, 0, 0);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(6, 3, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to x") {
    const auto transform = shearing(0, 0, 1, 0, 0, 0);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(2, 5, 4));
}

TEST_CASE("A shearing transformation moves y in proportion to z") {
    const auto transform = shearing(0, 0, 0, 1, 0, 0);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(2, 7, 4));
}

TEST_CASE("A shearing transformation moves z in proportion to x") {
    const auto transform = shearing(0, 0, 0, 0, 1, 0);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(2, 3, 6));
}

TEST_CASE("A shearing transformation moves z in proportion to y") {
    const auto transform = shearing(0, 0, 0, 0, 0, 1);
    const auto p = point(2, 3, 4);
    COMPARE_TUPLES(transform * p, point(2, 3, 7));
}

TEST_CASE("Individual transformations are applied in sequence") {
    const auto p = point(1, 0, 1);
    const auto A = rotationX(M_PI / 2);
    const auto B = scaling(5, 5, 5);
    const auto C = translation(10, 5, 7);

    // Apply rotation first
    const auto p2 = A * p;
    COMPARE_TUPLES(p2, point(1, -1, 0));

    // Then apply scaling
    const auto p3 = B * p2;
    COMPARE_TUPLES(p3, point(5, -5, 0));

    // Then apply translation
    const auto p4 = C * p3;
    COMPARE_TUPLES(p4, point(15, 0, 7));
}

TEST_CASE("Chained transformations must be applied in reverse order") {
    const auto p = point(1, 0, 1);
    const auto A = rotationX(M_PI / 2);
    const auto B = scaling(5, 5, 5);
    const auto C = translation(10, 5, 7);

    const auto T = C * B * A;
    COMPARE_TUPLES(T * p, point(15, 0, 7));
}

// TEST_CASE("The transformation matrix for the default orientation") {
//     const auto from = point(0, 0, 0);
//     const auto to = point(0, 0, -1);
//     const auto up = vector(0, 1, 0);
//
//     const auto t = viewTransform(from, to, up);
//     COMPARE_TUPLES(t * point(1, 0, 0), point(1, 0, 0));  // Ensure it's the identity matrix
// }
//
// TEST_CASE("A view transformation matrix looking in positive z direction") {
//     const auto from = point(0, 0, 0);
//     const auto to = point(0, 0, 1);
//     const auto up = vector(0, 1, 0);
//
//     const auto t = viewTransform(from, to, up);
//     COMPARE_TUPLES(t * point(1, 0, 0), point(-1, 0, 0));  // Ensure it's scaling(-1, 1, -1)
// }
//
// TEST_CASE("The view transformation moves the world") {
//     const auto from = point(0, 0, 8);
//     const auto to = point(0, 0, 0);
//     const auto up = vector(0, 1, 0);
//
//     const auto t = viewTransform(from, to, up);
//     COMPARE_TUPLES(t * point(0, 0, 0), point(0, 0, -8));  // Ensure it's translation(0, 0, -8)
// }
//
// TEST_CASE("An arbitrary view transformation") {
//     const auto from = point(1, 3, 2);
//     const auto to = point(4, -2, 8);
//     const auto up = vector(1, 1, 0);
//
//     const auto t = viewTransform(from, to, up);
//
//     // Expected matrix values
//     const auto expected = Matrix({
//         {-0.50709, 0.50709,  0.67612, -2.36643},
//         { 0.76772, 0.60609,  0.12122, -2.82843},
//         {-0.35857, 0.59761, -0.71714,  0.00000},
//         { 0.00000, 0.00000,  0.00000,  1.00000}
//     });
//
//     REQUIRE(t == expected);  // Assumes operator== is implemented for Matrix
// }
