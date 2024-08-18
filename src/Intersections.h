//
// Created by sam on 8/14/24.
//

#ifndef INTERSECTIONS_H
#define INTERSECTIONS_H



#include <vector>
#include <initializer_list>
#include <optional>

class Intersection;
#include "Intersection.h"

class Intersections : public std::vector<Intersection> {
public:
    // Variadic constructor using initializer list
    Intersections(std::initializer_list<Intersection> its);
    explicit Intersections(const std::vector<Intersection>& its);


    [[nodiscard]] std::optional<Intersection> hit() const;
};

#endif //INTERSECTIONS_H
