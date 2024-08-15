//
// Created by sam on 8/13/24.
//

#include "Color.h"

#include "Color.h"
#include <algorithm> // For std::clamp

// Constructor
Color::Color(const double e0, const double e1, const double e2, const double e3)
    : e {e0, e1, e2, e3 }, r(e[0]), g(e[1]), b(e[2]), a(e[3]) {}

// Member functions
Color Color::operator-() const {
    return Color {-e[0], -e[1], -e[2], -e[3] };
}

Color& Color::operator+=(const Color& v) {
    e[0] += v.e[0];
    e[1] += v.e[1];
    e[2] += v.e[2];
    return *this;
}

Color& Color::operator-=(const Color& v) {
    e[0] -= v.e[0];
    e[1] -= v.e[1];
    e[2] -= v.e[2];
    return *this;
}

Color& Color::operator*=(const double t) {
    e[0] *= t;
    e[1] *= t;
    e[2] *= t;
    return *this;
}

Color& Color::operator/=(const double t) {
    e[0] /= t;
    e[1] /= t;
    e[2] /= t;
    return *this;
}

std::array<int, 4> Color::RGB() const {
    return {
        static_cast<int>(std::clamp(e[0] * 255.0, 0.0, 255.0)),
        static_cast<int>(std::clamp(e[1] * 255.0, 0.0, 255.0)),
        static_cast<int>(std::clamp(e[2] * 255.0, 0.0, 255.0)),
        static_cast<int>(std::clamp(e[3] * 255.0, 0.0, 255.0))
    };
}

Color Color::operator*(const double t) const {
    return Color { e[0] * t, e[1] * t, e[2] * t, e[3] };
}

Color Color::operator*(const Color v) const {
    return Color { e[0] * v.e[0], e[1] * v.e[1], e[2] * v.e[2], e[3] };
}

Color Color::operator/(const double t) const {
    return Color { e[0] / t, e[1] / t, e[2] / t, e[3] };
}

Color Color::black() {
    return Color {0, 0, 0, 1};
}

Color Color::red() {
    return Color {1, 0, 0, 1};
}

Color Color::green() {
    return Color {0, 1, 0, 1};
}

Color Color::blue() {
    return Color {0, 0, 1, 1};
}

// Non-member functions
Color color(const double r, const double g, const double b) {
    return Color {r, g, b, 1};
}

Color operator+(const Color& u, const Color& v) {
    return Color {u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2], 1 };
}

Color operator-(const Color& u, const Color& v) {
    return Color {u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2], 1 };
}
