//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("Constructing and inspecting a 4x4 matrix") {
   const std::vector<float> e = { 1,2,3,4,5.5,6.5,7.5,8.5,9,10,11,12,13.5,14.5,15.5,16.5 };
    Matrix m { e };

    REQUIRE(m.element(0, 0) == Catch::Approx(1.0));
    REQUIRE(m.element(0, 3) == Catch::Approx(4.0));
    REQUIRE(m.element(1, 0) == Catch::Approx(5.5));
    REQUIRE(m.element(1, 2) == Catch::Approx(7.5));
    REQUIRE(m.element(2, 2) == Catch::Approx(11.0));
    REQUIRE(m.element(3, 0) == Catch::Approx(13.5));
    REQUIRE(m.element(3, 2) == Catch::Approx(15.5));
}

TEST_CASE("A 3x3 matrix ought to be representable") {
    const std::vector<float> e1 = { -3, 5, 0, 1, -2, -7, 0, 1, 1};
    const auto m = Matrix { e1 };

    REQUIRE(m.element(0, 0) == Catch::Approx(-3.0));
    REQUIRE(m.element(1, 1) == Catch::Approx(-2.0));
    REQUIRE(m.element(2, 2) == Catch::Approx(1.0));
}

TEST_CASE("A 2x2 matrix ought to be representable") {
    const std::vector<float> e = { -3, 5, 1, 2 };
    const Matrix m { e };
    REQUIRE(m.element(0, 0) == Catch::Approx(-3.0));
    REQUIRE(m.element(0, 1) == Catch::Approx(5.0));
    REQUIRE(m.element(1, 0) == Catch::Approx(1.0));
    REQUIRE(m.element(1, 1) == Catch::Approx(2.0));
}


TEST_CASE("Matrix equality with indentical matrices") {
    const std::vector<float> e1 = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    const Matrix a { e1};
    const std::vector<float> e2 = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    const Matrix b { e2};
    REQUIRE(a == b);
}

TEST_CASE("Matrix equality with different matrices") {
    const std::vector<float> e1= { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    const Matrix a { e1 };
    const std::vector<float> e2 = { 2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1 };
    const Matrix b { e2 };
    REQUIRE(a != b);
}

TEST_CASE("Multiplying two matrices") {
    const std::vector<float> e1 = { 1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2 };
    const Matrix a { e1};
    const std::vector<float> e2 = { -2,1,2,3,3,2,1,-1,4,3,6,5,1,2,7,8 };
    const Matrix b { e2};

    const Matrix result = a * b;
    const std::vector<float> e3 = { 20,22,50,48,44,54,114,108,40,58,110,102,16,26,46,42 };
    const Matrix expected { e3 };
    REQUIRE_MATRICES(result, expected);
}

TEST_CASE("Multiplying a matrix by a tuple") {
    const std::vector<float> e1 = { 1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1 };
    const auto a = Matrix { e1};
    const auto b = Tuple {1,2,3,1};
    REQUIRE_TUPLES(a * b, Tuple {18, 24, 33, 1});
}

TEST_CASE("Multiplying a matrix by the Identity Matrix") {
    const std::vector<float> e1 = { 1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1 };
    const auto a = Matrix {e1};
    const auto b = Matrix::Identity();
    REQUIRE_MATRICES(a * b, a);
}

TEST_CASE("Multiplying a tuple by the Identity Matrix") {
    float e1[16] = { 1,2,3,4,2,4,4,2,8,6,4,1,0,0,0,1 };
    const auto a = Tuple { 1,2,3,4};
    const auto b = Matrix::Identity();
    REQUIRE_TUPLES(b * a, a);
}

TEST_CASE("Transposing a matrix A") {
    const std::vector<float> e1 =
    {
        0,9,3,0,
        9,8,0,8,
        1,8,5,3,
        0,0,5,8
    };
    const auto a = Matrix {e1};
    const std::vector<float> e2 =
    {
        0,9,1,0,
        9,8,8,0,
        3,0,5,5,
        0,8,3,8
    };
    const auto b = Matrix {e2};

    REQUIRE_MATRICES(a.transpose(), b);
}

TEST_CASE("Calculating the determinant of a 2x2 matrix")
{
    const std::vector<float> e =
    {
        1,5,-3,2
    };
    const auto a = Matrix { e };

    REQUIRE(a.determinant() == Catch::Approx(17));
}

TEST_CASE("A submatrix of a 3x3 is a 2x2")
{
    const std::vector<float> e =
    {
        1,5,0,
        -3,2,7,
        0,6,-3
    };
    const auto a = Matrix { e };

    REQUIRE_MATRICES(a.subMatrix(0,2), Matrix {{-3,2,0,6}});
}

TEST_CASE("A submatrix of a 4x4 is a 3x3")
{
    const std::vector<float> e =
    {
        1,2,3,4,
        5,6,7,8,
        9,8,7,6,
        5,4,3,2
    };
    const auto a = Matrix { e };

    REQUIRE_MATRICES(a.subMatrix(2,1), Matrix {{1,3,4,5,7,8,5,3,2}});
}

TEST_CASE("Calculate a minor of a 3x3 matrix")
{
    const std::vector<float> e =
    {
        3,5,0,
        2,-1,-7,
        6,-1,5
    };
    const auto a = Matrix { e };

    const auto b = a.subMatrix(1,0);

    REQUIRE(b.determinant() == Catch::Approx(25));

    REQUIRE(a.minor(1,0) == Catch::Approx(25));
}

TEST_CASE("Calculate the cofactor of a 3x3 matrix") {
    // Given the following 3x3 matrix A:
    const std::vector<float> e = {
        3, 5, 0,
        2, -1, -7,
        6, -1, 5
    };
    const auto a = Matrix{e};

    // Then minor(A, 0, 0) should be -12
    REQUIRE(a.minor(0, 0) == Catch::Approx(-12));

    // And cofactor(A, 0, 0) should be -12
    REQUIRE(a.cofactor(0, 0) == Catch::Approx(-12));

    // And minor(A, 1, 0) should be 25
    REQUIRE(a.minor(1, 0) == Catch::Approx(25));

    // And cofactor(A, 1, 0) should be -25
    REQUIRE(a.cofactor(1, 0) == Catch::Approx(-25));
}

TEST_CASE("Calculate the cofactor and determinant of a 3x3 matrix") {
    // Given the following 3x3 matrix A:
    const std::vector<float> e = {
        1, 2, 6,
        -5, 8, -4,
        2, 6, 4
    };
    const auto a = Matrix{e};

    // Then cofactor(A, 0, 0) should be 56
    REQUIRE(a.cofactor(0, 0) == Catch::Approx(56));

    // And cofactor(A, 0, 1) should be 12
    REQUIRE(a.cofactor(0, 1) == Catch::Approx(12));

    // And cofactor(A, 0, 2) should be -46
    REQUIRE(a.cofactor(0, 2) == Catch::Approx(-46));

    // And determinant(A) should be -196
    REQUIRE(a.determinant() == Catch::Approx(-196));
}

TEST_CASE("Calculate the cofactor and determinant of a 4x4 matrix") {
    // Given the following 4x4 matrix A:
    const std::vector<float> e = {
        -2, -8,  3,  5,
        -3,  1,  7,  3,
         1,  2, -9,  6,
        -6,  7,  7, -9
    };
    const auto a = Matrix{e};

    // Then cofactor(A, 0, 0) should be 690
    REQUIRE(a.cofactor(0, 0) == Catch::Approx(690));

    // And cofactor(A, 0, 1) should be 447
    REQUIRE(a.cofactor(0, 1) == Catch::Approx(447));

    // And cofactor(A, 0, 2) should be 210
    REQUIRE(a.cofactor(0, 2) == Catch::Approx(210));

    // And cofactor(A, 0, 3) should be 51
    REQUIRE(a.cofactor(0, 3) == Catch::Approx(51));

    // And determinant(A) should be -4071
    REQUIRE(a.determinant() == Catch::Approx(-4071));
}

TEST_CASE("Testing an invertible matrix for invertibility") {
    // Given the following 4x4 matrix A:
    const std::vector<float> e = {
        6,  4,  4,  4,
        5,  5,  7,  6,
        4, -9,  3, -7,
        9,  1,  7, -6
    };
    const auto a = Matrix{e};

    // Then determinant(A) should be -2120
    REQUIRE(a.determinant() == Catch::Approx(-2120));

    // And A should be invertible
    REQUIRE(a.determinant() != 0);
}

TEST_CASE("Testing a noninvertible matrix for invertibility") {
    // Given the following 4x4 matrix A:
    const std::vector<float> e = {
        -4,  2, -2, -3,
         9,  6,  2,  6,
         0, -5,  1, -5,
         0,  0,  0,  0
    };
    const auto a = Matrix{e};

    // Then determinant(A) should be 0
    REQUIRE(a.determinant() == Catch::Approx(0));

    // And A should not be invertible
    REQUIRE(a.determinant() == 0);
}

TEST_CASE("Calculating the inverse of a matrix") {
    // Given the following 4x4 matrix A:
    const std::vector<float> e = {
        -5,  2,  6, -8,
         1, -5,  1,  8,
         7,  7, -6, -7,
         1, -3,  7,  4
    };
    const auto a = Matrix{e};

    // And B ← inverse(A)
    const auto b = a.inverse();

    // Then determinant(A) should be 532
    REQUIRE(a.determinant() == Catch::Approx(532).epsilon(0.001));

    // And cofactor(A, 2, 3) should be -160
    REQUIRE(a.cofactor(2, 3) == Catch::Approx(-160).epsilon(0.001));

    // And B[3,2] should be -160/532
    REQUIRE(b.element(3, 2) == Catch::Approx(-160.0 / 532.0).epsilon(0.001));

    // And cofactor(A, 3, 2) should be 105
    REQUIRE(a.cofactor(3, 2) == Catch::Approx(105).epsilon(0.001));

    // And B[2,3] should be 105/532
    REQUIRE(b.element(2, 3) == Catch::Approx(105.0 / 532.0).epsilon(0.001));

    // And B should be the following 4x4 matrix:
    const std::vector<float> expected = {
        0.21805, 0.45113, 0.24060, -0.04511,
       -0.80827, -1.45677, -0.44361, 0.52068,
       -0.07895, -0.22368, -0.05263, 0.19737,
       -0.52256, -0.81391, -0.30075, 0.30639
    };
    const auto expectedMatrix = Matrix{expected};

    REQUIRE(b == expectedMatrix);
}

TEST_CASE("Calculating the inverse of more matrices") {
    SECTION("First matrix") {
        const std::vector<float> e1 = {
            8, -5, 9, 2,
            7, 5, 6, 1,
            -6, 0, 9, 6,
            -3, 0, -9, -4
        };
        const Matrix A(e1);

        const std::vector<float> expected_inverse1 = {
            -0.15385, -0.15385, -0.28205, -0.53846,
            -0.07692, 0.12308, 0.02564, 0.03077,
            0.35897, 0.35897, 0.43590, 0.92308,
            -0.69231, -0.69231, -0.76923, -1.92308
        };
        const Matrix expected_inverse1_matrix(expected_inverse1);

        const Matrix actual_inverse = A.inverse();

        REQUIRE(actual_inverse == expected_inverse1_matrix);
    }

    SECTION("Second matrix") {
        const std::vector<float> e2 = {
            9, 3, 0, 9,
            -5, -2, -6, -3,
            -4, 9, 6, 4,
            -7, 6, 6, 2
        };
        const Matrix A(e2);

        const std::vector<float> expected_inverse2 = {
            -0.04074, -0.07778, 0.14444, -0.22222,
            -0.07778, 0.03333, 0.36667, -0.33333,
            -0.02901, -0.14630, -0.10926, 0.12963,
            0.17778, 0.06667, -0.26667, 0.33333
        };
        const Matrix expected_inverse2_matrix(expected_inverse2);

        const Matrix actual_inverse = A.inverse();

        REQUIRE(actual_inverse == expected_inverse2_matrix);
    }
}

TEST_CASE("Multiplying a product by its inverse") {
    // Define matrix A
    const std::vector<float> eA = {
        3, -9,  7,  3,
        3, -8,  2, -9,
        -4,  4,  4,  1,
        -6,  5, -1,  1
    };
    const Matrix A(eA);

    // Define matrix B
    const std::vector<float> eB = {
        8,  2,  2,  2,
        3, -1,  7,  0,
        7,  0,  5,  4,
        6, -2,  0,  5
    };
    const Matrix B { eB };

    // Compute the product C = A * B
    const Matrix C = A * B;

    // Compute the inverse of matrix B
    const Matrix B_inv = B.inverse();

    // Compute C * inverse(B)
    const Matrix result = C * B_inv;

    // Verify that result equals A
    REQUIRE(result == A);
}