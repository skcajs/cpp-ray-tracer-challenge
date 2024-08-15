//
// Created by sam on 8/13/24.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Intersections.h"
#include "Matrix.h"
#include "Ray.h"


class Sphere {
public:
    Point origin;
    mutable Matrix transform = Matrix::Identity();
    explicit Sphere(const Point &origin  = point(0,0,0));

    [[nodiscard]] Intersections intersect(const Ray &r) const;
    void setTransform(const Matrix& m) const;

    Vector normalAt(const Point &worldPoint) const;
};

inline bool operator==(const Sphere &lhs, const Sphere &rhs) {
    return lhs.origin == rhs.origin;
}

#endif //SPHERE_H
