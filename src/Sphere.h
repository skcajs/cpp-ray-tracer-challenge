//
// Created by sam on 8/13/24.
//

#ifndef SPHERE_H
#define SPHERE_H
#include <vector>

#include "Intersections.h"
#include "Ray.h"


class Sphere {
public:
    Point origin;
    explicit Sphere(const Point &origin  = point(0,0,0));

    [[nodiscard]] Intersections intersects(const Ray &r) const;
};

inline bool operator==(const Sphere &lhs, const Sphere &rhs) {
    return lhs.origin == rhs.origin;
}



#endif //SPHERE_H
