//
// Created by sam on 8/13/24.
//

#include "Sphere.h"
#include "Intersection.h"

#include <cmath>

Sphere::Sphere(const Point &origin) : origin(origin) {}

Intersections Sphere::intersect(const Ray &r) const {
    const auto r2 = r.transform(transform.inverse());
    auto result = Intersections {};
    const auto sphereToRay = r2.origin - origin;
    const auto a = r2.direction.dot(r2.direction);
    const auto b = 2 * r2.direction.dot(sphereToRay);
    const auto c = sphereToRay.dot(sphereToRay) - 1;

    if (const auto discriminant = pow(b,2) - 4 * a * c; discriminant >= 0) {
        result.emplace_back(Intersection{(-b - sqrt(discriminant)) / (2 * a), this});
        result.emplace_back(Intersection{(-b + sqrt(discriminant)) / (2 * a), this});
    }
    return result;
}

void Sphere::setTransform(const Matrix &m) const {
    transform = m;
}
