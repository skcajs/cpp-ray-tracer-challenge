//
// Created by sam on 8/16/24.
//

#ifndef INTERVAL_H
#define INTERVAL_H

#include <cmath>

class Interval {
public:
    double min, max;

    Interval() : min(+INFINITY), max(-INFINITY) {} // Default interval is empty

    Interval(const double min, const double max) : min(min), max(max) {}

    [[nodiscard]] double size() const {
        return max - min;
    }

    [[nodiscard]] bool contains(const double x) const {
        return min <= x && x <= max;
    }

    [[nodiscard]] bool surrounds(const double x) const {
        return min < x && x < max;
    }

    [[nodiscard]] double clamp(const double x) const {
        if (x < min) return min;
        if (x > max) return max;
        return x;
    }

    static const Interval empty, universe;
};

const Interval Interval::empty    = Interval(+INFINITY, -INFINITY);
const Interval Interval::universe = Interval(-INFINITY, +INFINITY);


#endif
