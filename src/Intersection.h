//
// Created by sam on 8/14/24.
//

#ifndef INTERSECTION_H
#define INTERSECTION_H
#include "Sphere.h"


class Intersection {
public:
    double t;
    Sphere object;
    Intersection(double t, const Sphere &object);
};



#endif //INTERSECTION_H
