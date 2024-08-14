//
// Created by sam on 8/13/24.
//

#include "Ray.h"

Ray::Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction) {}

Point Ray::position(const float t) const {
    return origin + direction * t;
}
