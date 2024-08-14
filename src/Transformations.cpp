//
// Created by sam on 8/13/24.
//

#include "Transformations.h"
#include <cmath>

Matrix translation(float x, float y, float z) {
    return Matrix {
            {
                1, 0, 0, x,
                0, 1, 0, y,
                0, 0, 1, z,
                0, 0, 0, 1
            }
    };
}

Matrix scaling(float x, float y, float z) {
    return Matrix {
            {
                x, 0, 0, 0,
                0, y, 0, 0,
                0, 0, z, 0,
                0, 0, 0, 1
            }
    };
}

Matrix rotationX(const float angle) {
    return Matrix {
            {
                1, 0, 0, 0,
                0, std::cos(angle), -std::sin(angle), 0,
                0, std::sin(angle), std::cos(angle), 0,
                0, 0, 0, 1
            }
    };
}

Matrix rotationY(const float angle) {
    return Matrix {
            {
                std::cos(angle), 0, std::sin(angle), 0,
                0, 1, 0, 0,
                -std::sin(angle), 0, std::cos(angle), 0,
                0, 0, 0, 1
            }
    };
}

Matrix rotationZ(const float angle) {
    return Matrix {
            {
                std::cos(angle), -std::sin(angle), 0, 0,
                std::sin(angle), std::cos(angle), 0, 0,
                0, 0, 1, 0,
                0, 0, 0, 1
            }
    };
}

Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy) {
    return Matrix {
            {
                1, xy, xz, 0,
                yx, 1, yz, 0,
                zx, zy, 1, 0,
                0, 0, 0, 1
            }
    };
}
