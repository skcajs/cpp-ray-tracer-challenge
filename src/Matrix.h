//
// Created by sam on 8/13/24.
//

#ifndef MATRIX_H
#define MATRIX_H

#pragma once
#include <cmath>
#include <vector>

#include "Tuple.h"

class Matrix {
public:
    explicit Matrix(const std::vector<double> &data);
    explicit Matrix(std::size_t size);
    Matrix(const Matrix& other);

    Matrix& operator=(const Matrix& other);
    Tuple operator*(const Tuple& other) const;

    [[nodiscard]] double element(int row, int col) const;
    void setElement(int row, int col, double value) const;

    [[nodiscard]] auto Size() const { return size; }

    [[nodiscard]] Matrix transpose() const;
    [[nodiscard]] double determinant() const;
    [[nodiscard]] Matrix subMatrix(int rowToRemove, int colToRemove) const;
    [[nodiscard]] double minor(int row, int col) const;
    [[nodiscard]] double cofactor(int row, int col) const;
    [[nodiscard]] bool isInvertible() const;
    [[nodiscard]] Matrix inverse() const;

    static Matrix Identity();

    ~Matrix();

private:
    std::size_t size;
    double** e{};

    void allocateMatrix(std::size_t size);
    void deallocateMatrix() const;
    void copyMatrix(const Matrix& other) const;
};

inline bool operator==(const Matrix& u, const Matrix& v) {
    const auto size = u.Size();

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            if (constexpr double tolerance = 1e-4; std::abs(u.element(i, j) - v.element(i, j)) > tolerance) {
                return false;
            }
        }
    }
    return true;
}

inline Matrix operator*(const Matrix& u, const Matrix& v) {
    const auto size = u.Size();

    // Create the result matrix with dimensions uRows x vCols
    Matrix result { size };

    // Perform the matrix multiplication
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            double sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += u.element(i, k) * v.element(k, j);
            }
            result.setElement(i, j, sum);
        }
    }
    return result;
}



#endif //MATRIX_H
