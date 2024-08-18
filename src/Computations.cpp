//
// Created by sam on 8/18/24.
//

#include "Computations.h"

Computations::Computations(
    const double t, const Sphere *object, const Point &pos, const Vector &eye, const Vector &normal)
        : t(t), object(object), pos(pos), eye(eye), normal(normal) {
    if (normal.dot(eye) < 0) {
        this->inside = true;
        this->normal = -normal;
    }
}
