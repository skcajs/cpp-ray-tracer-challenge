//
// Created by sam on 8/18/24.
//

#ifndef COMPUTATIONS_H
#define COMPUTATIONS_H
#include <vector>

#include "Tuple.h"


class Sphere;

struct Computations {
    double t;
    const Sphere *object;
    Point pos;
    Vector eye;
    Vector normal;
    bool inside = false;

    Computations( double t, const Sphere* object, const Point &pos, const Vector &eye, const Vector &normal);
};



#endif //COMPUTATIONS_H
