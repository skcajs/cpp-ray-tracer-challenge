//
// Created by sam on 8/13/24.
//

#include "Sphere.h"
#include "Intersection.h"

#include <cmath>

Sphere::Sphere(const Point &origin) : origin(origin) {}
Sphere::Sphere(const Sphere &sphere) = default;

Sphere& Sphere::operator=(const Sphere& sphere) {
    if (this == &sphere) return *this;
    origin = sphere.origin;
    transform = sphere.transform;
    material = sphere.material;
    return *this;
}

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

void Sphere::setTransform(const Matrix &m) {
    transform = m;
}

Vector Sphere::normalAt(const Point &worldPoint) const {
    const auto objectPoint = transform.inverse() * worldPoint;
    const auto objectNormal = objectPoint - origin;
    const auto worldNormal = transform.inverse().transpose() * objectNormal;
    worldNormal.resetWVector(); // Dont like this
    return worldNormal.normalize();
}

bool operator==(const Sphere &lhs, const Sphere &rhs) {
    return lhs.origin == rhs.origin && lhs.transform == rhs.transform && lhs.material == rhs.material;
}
