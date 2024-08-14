//
// Created by sam on 8/13/24.
//

#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include "Matrix.h"

class Transformations {

};

Matrix translation(float x, float y, float z);
Matrix scaling(float x, float y, float z);
Matrix rotationX(float angle);
Matrix rotationY(float angle);
Matrix rotationZ(float angle);
Matrix shearing(float xy, float xz, float yx, float yz, float zx, float zy);

#endif // TRANSFORMATIONS_H

