//
// Created by sam on 8/13/24.
//

#include "Sphere.h"

Sphere::Sphere(const Point &origin) : origin(origin) {}

std::vector<double> Sphere::intersects(const Ray &r) const {
    auto result = std::vector<double>();
    const auto sphereToRay = r.origin - origin;
    const auto a = r.direction.dot(r.direction);
    const auto b = 2 * r.direction.dot(sphereToRay);
    const auto c = sphereToRay.dot(sphereToRay) - 1;

    if (const auto discriminant = pow(b,2) - 4 * a * c; discriminant >= 0) {
        result.emplace_back((-b - sqrt(discriminant)) / (2 * a));
        result.emplace_back((-b + sqrt(discriminant)) / (2 * a));
    }
    return result;
}
