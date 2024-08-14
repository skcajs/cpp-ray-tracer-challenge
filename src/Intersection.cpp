//
// Created by sam on 8/14/24.
//

#include "Intersection.h"

Intersection::Intersection(const double t, const Sphere* object) : t(t), object(object) {}

bool Intersection::operator==(const Intersection &other) const {
    return t == other.t && object == other.object;
}
