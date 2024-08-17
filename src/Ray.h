//
// Created by sam on 8/13/24.
//

#ifndef RAY_H
#define RAY_H
#include "Tuple.h"


class Matrix;

class Ray {
public:
    Point origin;
    Vector direction;

    Ray(const Point &origin, const Vector &direction);

    [[nodiscard]] Point position(double t) const;
    [[nodiscard]] Ray transform(const Matrix &m) const;
};



#endif //RAY_H
