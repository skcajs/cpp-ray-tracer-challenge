//
// Created by sam on 8/18/24.
//

#include "World.h"

#include <algorithm>

#include "Transformations.h"

World::World() = default;

World::World(std::vector<Sphere> objects, const std::optional<Light> &light): objects(std::move(objects)), light(light) {}

Intersections World::intersectWorld(const Ray &ray) const {
    std::vector<Intersection> allIntersections;

    for (const auto& obj : objects) {
        auto intersections = obj.intersect(ray);
        allIntersections.insert(allIntersections.end(), intersections.begin(), intersections.end());
    }

    // Sort intersections by the t value
    std::ranges::sort(allIntersections,
                      [](const Intersection& a, const Intersection& b) {
                          return a.t < b.t;
                      });

    return Intersections(allIntersections);
}

Color World::shadeHit(const Computations &comps) const {
    return comps.object->material.lighting(light.value(), comps.pos, comps.eye, comps.normal);
}

Color World::colorAt(const Ray &ray) const {
    if (const auto hit = intersectWorld(ray).hit(); hit.has_value()) {
        return shadeHit(hit->prepare_computations(ray));
    }
    return Color::black();
}

World defaultWorld() {

    const auto light = pointLight(point(-10, 10, -10), color(1,1,1));

    Sphere s1 {};
    s1.material.color = color(0.8,1.0,0.6);
    s1.material.diffuse = 0.7;
    s1.material.specular = 0.2;

    Sphere s2 {};
    s2.transform = scaling(0.5,0.5,0.5);

    std::vector<Sphere> objects;
    objects.emplace_back(s1);
    objects.emplace_back(s2);

    return World { objects, light };
}
