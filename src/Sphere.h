//
// Created by sam on 8/13/24.
//

#ifndef SPHERE_H
#define SPHERE_H

#include "Intersections.h"
#include "Material.h"
#include "Matrix.h"
#include "Ray.h"

class Sphere {
public:
    Point origin;
    Matrix transform = Matrix::Identity();
    Material material;

    explicit Sphere(const Point &origin  = point(0,0,0));
    Sphere(const Sphere& sphere);

    Sphere& operator=(const Sphere& sphere);

    [[nodiscard]] Intersections intersect(const Ray &r) const;
    void setTransform(const Matrix& m);

    Vector normalAt(const Point &worldPoint) const;
};

bool operator==(const Sphere &lhs, const Sphere &rhs);

#endif //SPHERE_H
