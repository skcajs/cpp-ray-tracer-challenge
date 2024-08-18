#include "Matrix.h"

#include <stdexcept>

Matrix::Matrix(const std::vector<double>& data) : size(static_cast<std::size_t>(std::sqrt(data.size()))), e(data) {
    if (size * size != data.size()) {
        throw std::invalid_argument("Invalid data size for a square matrix.");
    }
}

Matrix::Matrix(const std::size_t size) : size(size), e(size * size, 0.0) {}

Matrix& Matrix::operator=(const Matrix& other) {
    if (this != &other) {
        size = other.size;
        e = other.e;
    }
    return *this;
}

std::size_t Matrix::index(const int row, const int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return row * size + col;
}

double Matrix::element(const int row, const int col) const {
    return e[index(row, col)];
}

void Matrix::setElement(const int row, const int col, const double value) {
    e[index(row, col)] = value;
}

std::vector<double> Matrix::getElements() const {
    return e;
}

Tuple Matrix::operator*(const Tuple& other) const {
    if (size != 4) {
        throw std::invalid_argument("Matrix must be 4x4 to multiply with a 4-dimensional tuple.");
    }

    return {
        e[index(0,0)] * other.x + e[index(0,1)] * other.y + e[index(0,2)] * other.z + e[index(0,3)] * other.w,
        e[index(1,0)] * other.x + e[index(1,1)] * other.y + e[index(1,2)] * other.z + e[index(1,3)] * other.w,
        e[index(2,0)] * other.x + e[index(2,1)] * other.y + e[index(2,2)] * other.z + e[index(2,3)] * other.w,
        e[index(3,0)] * other.x + e[index(3,1)] * other.y + e[index(3,2)] * other.z + e[index(3,3)] * other.w
    };
}

Matrix Matrix::operator*(const Matrix &other) const {
    if (size != other.size) {
        throw std::invalid_argument("Both matrices must be of the same size for multiplication.");
    }

    Matrix result(size); // Create an empty matrix for the result

    for (int row = 0; row < size; ++row) {
        for (int col = 0; col < size; ++col) {
            double sum = 0;
            for (int k = 0; k < size; ++k) {
                sum += e[index(row, k)] * other.e[other.index(k, col)];
            }
            result.e[result.index(row, col)] = sum;
        }
    }
    return result;
}

Matrix Matrix::Identity() {

    return Matrix {
        {
            1,0,0,0,
            0,1,0,0,
            0,0,1,0,
            0,0,0,1
        }};
}

Matrix Matrix::transpose() const {
    Matrix result {size};

    // Populate the transposed matrix
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            result.setElement(j, i, this->element(i, j));
        }
    }
    return result;
}

double Matrix::determinant() const { // NOLINT(*-no-recursion)
    double det = 0;

    if (size == 2) {
        det = e[index(0,0)] * e[index(1,1)] - e[index(0,1)] * e[index(1,0)];
    } else {
        for (int i = 0; i < size; ++i) {
            det += e[index(0,i)] * cofactor(0, i);
        }
    }
    return det;
}

Matrix Matrix::subMatrix(const int rowToRemove, const int colToRemove) const {
    // Check if the indices are within bounds
    if (rowToRemove < 0 || rowToRemove >= size || colToRemove < 0 || colToRemove >= size) {
        throw std::out_of_range("Row or column index out of range");
    }

    // Create the submatrix with size reduced by 1
    Matrix sub(size - 1);

    int subRow = 0;

    for (int i = 0; i < size; ++i) {
        if (i == rowToRemove) continue; // Skip the row to remove
        int subCol = 0; // Reset column index for each new row in the submatrix
        for (int j = 0; j < size; ++j) {
            if (j == colToRemove) continue; // Skip the column to remove
            sub.e[sub.index(subRow, subCol)] = e[index(i, j)];
            ++subCol;
        }
        ++subRow;
    }
    return sub;
}

double Matrix::minor(const int row, const int col) const { // NOLINT(*-no-recursion)
    if (size <= 1) {
        throw std::invalid_argument("Minor is not defined for matrices of size 1x1 or smaller");
    }
    return subMatrix(row, col).determinant();
}

double Matrix::cofactor(const int row, const int col) const { // NOLINT(*-no-recursion)
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Matrix index out of range");
    }

    // Calculate the minor of the element at (row, col)
    const double minorValue = minor(row, col);

    // Calculate the cofactor
    const double cofactorValue = (static_cast<double>((row + col) % 2 == 0 ? 1 : -1)) * minorValue;;

    return cofactorValue;
}

bool Matrix::isInvertible() const {
    return determinant() != 0;
}

Matrix Matrix::inverse() const {
    if(!isInvertible()) {
        throw std::invalid_argument("Matrix is not invertible");
    }
    Matrix m { size };
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            const auto c = cofactor(i, j);
            m.setElement(j, i, c / determinant());
        }
    }
    return m;
}

bool operator==(const Matrix &lhs, const Matrix &rhs) {
    return lhs.getElements()  == rhs.getElements();
}
