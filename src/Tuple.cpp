//
// Created by sam on 8/12/24.
//

#include "Tuple.h"
#include <cmath>

Tuple::Tuple() : e{0, 0, 0, 0}, x(0), y(e[1]), z(e[2]), w(e[3]) {
}

Tuple::Tuple(const double e0, const double e1, const double e2, const double e3) : e{e0, e1, e2, e3},  x(e[0]), y(e[1]), z(e[2]), w(e[3]) {
}

Tuple Tuple::operator-() const {
    return Tuple {-e[0], -e[1], -e[2], -e[3]};
}

Tuple& Tuple::operator+=(const Tuple& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Tuple& Tuple::operator-=(const Tuple& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

Tuple& Tuple::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    e[3] *= t;
    return *this;
}

Tuple& Tuple::operator/=(const double t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    e[3] /= t;
    return *this;
}

Tuple Tuple::operator*(const double t) const {
    return Tuple { e[0] * t, e[1] * t, e[2] * t, e[3] * t };
}

Tuple Tuple::operator/(const double t) const {
    return Tuple { e[0] / t, e[1] / t, e[2] / t, e[3] / t };
}

[[nodiscard]] double Tuple::norm() const {
    return std::sqrt(e[0] * e[0] + e[1] * e[1] + e[2] * e[2]);
}

[[nodiscard]] Tuple Tuple::normalize() const {
    const double length = norm();
    return Tuple { e[0] / length, e[1] / length, e[2] / length, e[3] / length };
}

[[nodiscard]] double Tuple::dot(const Tuple& v) const {
    return e[0] * v.e[0] + e[1] * v.e[1] + e[2] * v.e[2] + e[3] * v.e[3];
}

[[nodiscard]] Tuple Tuple::cross(const Tuple& v) const {
    return Tuple {
        e[1] * v.e[2] - e[2] * v.e[1],
        e[2] * v.e[0] - e[0] * v.e[2],
        e[0] * v.e[1] - e[1] * v.e[0],
        e[0] * v.e[1] - e[1] * v.e[0]
    };
}

void Tuple::resetWVector() const{
    e[3] = 0;
}

void Tuple::resetWPoint() const{
    e[3] = 1;
}

Vector Tuple::reflect(const Tuple &normal) const {
    return *this - (normal * 2 * this->dot(normal));
}

Tuple point(const double x, const double y, const double z) {
    return Point {x, y, z, 1};
}

Tuple vector(const double x, const double y, const double z) {
    return Vector {x, y, z, 0};
}

Tuple operator+(const Tuple& u, const Tuple& v) {
    return Tuple {u.x + v.x, u.y + v.y, u.z + v.z, u.w + v.w};
}

Tuple operator-(const Tuple& u, const Tuple& v) {
    return Tuple {u.x - v.x, u.y - v.y, u.z - v.z, u.w - v.w};
}