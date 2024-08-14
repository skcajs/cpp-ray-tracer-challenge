//
// Created by sam on 8/13/24.
//

#include "Ray.h"

#include <iostream>

#include "Matrix.h"

Ray::Ray(const Point& origin, const Vector& direction): origin(origin), direction(direction) {}

Point Ray::position(const float t) const {
    return origin + direction * t;
}

Ray Ray::transform(const Matrix &m) const {
    const Tuple transformedOrigin = m * origin;
    const Tuple transformedDirection = m * direction;

    std::cout << "Transformed origin: " << transformedOrigin.x << ", " << transformedOrigin.y << ", " << transformedOrigin.z << ", " << transformedOrigin.w << std::endl;
    std::cout << "Transformed direction: " << transformedDirection.x << ", " << transformedDirection.y << ", " << transformedDirection.z << ", " << transformedDirection.w << std::endl;

    return Ray {transformedOrigin, transformedDirection};
}
