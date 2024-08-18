//
// Created by sam on 8/18/24.
//

#ifndef WORLD_H
#define WORLD_H
#include <optional>
#include <vector>

#include "Light.h"
#include "Sphere.h"

class World {
public:
    std::vector<Sphere> objects;
    std::optional<Light> light;

    World();
    World(std::vector<Sphere> objects, const std::optional<Light> &light);

    Intersections intersectWorld(const Ray &ray) const;

    Color shadeHit(const Computations &comps) const;
    Color colorAt(const Ray &ray) const;
};

World defaultWorld();

#endif //WORLD_H
