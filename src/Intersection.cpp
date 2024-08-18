//
// Created by sam on 8/14/24.
//

#include "Intersection.h"

#include "Computations.h"
#include "Sphere.h"

Intersection::Intersection(const double t, const Sphere* object) : t(t), object(object) {}

bool Intersection::operator==(const Intersection &other) const {
    return t == other.t && object == other.object;
}

Computations Intersection::prepare_computations(const Ray &ray) const {
    return Computations { t, object, ray.position(t), -ray.direction, object->normalAt(ray.position((t))) };
}
