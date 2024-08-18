//
// Created by sam on 8/15/24.
//

#include "Light.h"

Light::Light(const Point &position, const Color &intensity) : position(position), intensity(intensity) {}

bool operator==(const Light &lhs, const Light &rhs) {
    return lhs.intensity == rhs.intensity && lhs.position == rhs.position;
}

Light pointLight(const Point &position, const Color &intensity) {
    return Light { position, intensity };
}

