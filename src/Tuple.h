//
// Created by sam on 8/12/24.
//

#ifndef TUPLE_H
#define TUPLE_H

class Tuple {
public:
    double e[4];

    // Constructors
    Tuple();
    Tuple(double e0, double e1, double e2, double e3);

    // Accessors
    double& x;
    double& y;
    double& z;
    double& w;

    // Unary operations
    Tuple operator-() const;

    // Compound assignment operators
    Tuple& operator+=(const Tuple& v);
    Tuple& operator-=(const Tuple& v);
    Tuple& operator*=(double t);
    Tuple& operator/=(double t);

    // Binary operators
    Tuple operator*(double t) const;
    Tuple operator/(double t) const;

    // Member functions
    [[nodiscard]] double norm() const;
    [[nodiscard]] Tuple normalize() const;
    [[nodiscard]] double dot(const Tuple& v) const;
    [[nodiscard]] Tuple cross(const Tuple& v) const;
};

using Point = Tuple;
using Vector = Tuple;

// Free functions
Point point(double x = 0, double y = 0, double z = 0);
Vector vector(double x = 0, double y = 0, double z = 0);

Tuple operator+(const Tuple& u, const Tuple& v);
Tuple operator-(const Tuple& u, const Tuple& v);

inline bool operator==(const Tuple &lhs, const Tuple &rhs) {
    return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
}

#endif // TUPLE_H

