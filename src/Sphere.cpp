//
// Created by sam on 8/13/24.
//

#include "Sphere.h"

#include "Intersection.h"

Sphere::Sphere(const Point &origin) : origin(origin) {}

Intersections Sphere::intersects(const Ray &r) const {
    auto result = Intersections {};
    const auto sphereToRay = r.origin - origin;
    const auto a = r.direction.dot(r.direction);
    const auto b = 2 * r.direction.dot(sphereToRay);
    const auto c = sphereToRay.dot(sphereToRay) - 1;

    if (const auto discriminant = pow(b,2) - 4 * a * c; discriminant >= 0) {
        result.emplace_back(Intersection{(-b - sqrt(discriminant)) / (2 * a), this});
        result.emplace_back(Intersection{(-b + sqrt(discriminant)) / (2 * a), this});
    }
    return result;
}
