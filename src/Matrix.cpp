#include "Matrix.h"

#include <stdexcept>

Matrix::Matrix(const std::vector<double> &data) : size(static_cast<std::size_t>(std::sqrt(data.size()))){

    if (size < 0) {
        throw std::invalid_argument("Matrix dimensions must be positive");
    }

    allocateMatrix(size);

    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            e[i][j] = data[i * size + j];
        }
    }
}

Matrix::Matrix(const std::size_t size) : size(size) {
    allocateMatrix(size);
}

Tuple Matrix::operator*(const Tuple& other) const {
    if (size != 4) {
        throw std::invalid_argument("Matrix must be 4x4 to multiply with a 4-dimensional tuple.");
    }

    return {
        e[0][0] * other.x + e[0][1] * other.y + e[0][2] * other.z + e[0][3] * other.w,
        e[1][0] * other.x + e[1][1] * other.y + e[1][2] * other.z + e[1][3] * other.w,
        e[2][0] * other.x + e[2][1] * other.y + e[2][2] * other.z + e[2][3] * other.w,
        e[3][0] * other.x + e[3][1] * other.y + e[3][2] * other.z + e[3][3] * other.w
    };
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
    const Matrix result {size};

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
        det = e[0][0] * e[1][1] - e[0][1] * e[1][0];
    } else {
        for (int i = 0; i < size; ++i) {
            det += e[0][i] * cofactor(0, i);
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

    std::size_t subRow = 0;

    for (int i = 0; i < size; ++i) {
        if (i == rowToRemove) continue; // Skip the row to remove
        std::size_t subCol = 0; // Reset column index for each new row in the submatrix
        for (int j = 0; j < size; ++j) {
            if (j == colToRemove) continue; // Skip the column to remove
            sub.e[subRow][subCol] = e[i][j];
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
    const Matrix m { size };
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < size; ++j) {
            const auto c = cofactor(i, j);
            m.setElement(j, i, c / determinant());
        }
    }
    return m;
}

Matrix::~Matrix() {
    deallocateMatrix();
}

void Matrix::allocateMatrix(const std::size_t size) {
    e = new double*[size];
    for (int i = 0; i < size; ++i) {
        e[i] = new double[size];
    }
}

void Matrix::deallocateMatrix() const {
    for (int i = 0; i < size; ++i) {
        delete[] e[i];
    }
    delete[] e;
}

double Matrix::element(const int row, const int col) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Matrix index out of range");
    }
    return e[row][col];
}

void Matrix::setElement(const int row, const int col, const double value) const {
    if (row < 0 || row >= size || col < 0 || col >= size) {
        throw std::out_of_range("Matrix index out of range");
    }
    e[row][col] = value;
}