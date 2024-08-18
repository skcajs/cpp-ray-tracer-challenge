//
// Created by sam on 8/14/24.
//

#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Computations.h"
#include "Ray.h"

class Sphere;

class Intersection {
public:
    double t;
    const Sphere* object;
    Intersection(double t, const Sphere* object);

    bool operator==(const Intersection& other) const;

    [[nodiscard]] Computations prepare_computations(const Ray & ray) const;
};


#endif //INTERSECTION_H
