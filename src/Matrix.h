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
    explicit Matrix(const std::vector<double>& data);
    explicit Matrix(std::size_t size);

    Matrix& operator=(const Matrix& other);
    Tuple operator*(const Tuple& other) const;
    Matrix operator*(const Matrix& other) const;

    [[nodiscard]] double element(int row, int col) const;
    [[nodiscard]] std::vector<double> getElements() const;
    void setElement(int row, int col, double value);

    [[nodiscard]] auto Size() const { return size; }

    [[nodiscard]] Matrix transpose() const;
    [[nodiscard]] double determinant() const;
    [[nodiscard]] Matrix subMatrix(int rowToRemove, int colToRemove) const;
    [[nodiscard]] double minor(int row, int col) const;
    [[nodiscard]] double cofactor(int row, int col) const;
    [[nodiscard]] bool isInvertible() const;
    [[nodiscard]] Matrix inverse() const;

    static Matrix Identity();

private:
    std::size_t size;
    std::vector<double> e;  // Single vector to store matrix elements

    [[nodiscard]] std::size_t index(int row, int col) const;  // Helper to convert 2D indices to 1D
};

bool operator==(const Matrix &lhs, const Matrix &rhs);



#endif //MATRIX_H
