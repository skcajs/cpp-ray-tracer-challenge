//
// Created by sam on 8/14/24.
//

#include "Intersections.h"

Intersections::Intersections(const std::initializer_list<Intersection> its) : std::vector<Intersection>(its) {}

Intersections::Intersections(const std::vector<Intersection> &its) : std::vector<Intersection>(its) {}

std::optional<Intersection> Intersections::hit() const {
    std::optional<Intersection> closest = std::nullopt;
    for (const auto& intersection : *this) {
        if (intersection.t > 0 && (!closest.has_value() || intersection.t < closest->t)) {
            closest = intersection;
        }
    }
    return closest;
}


