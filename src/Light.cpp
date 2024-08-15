//
// Created by sam on 8/15/24.
//

#include "Light.h"

Light::Light(const Point &position, const Color &intensity) : position(position), intensity(intensity) {}

Light pointLight(const Point &position, const Color &intensity) {
    return Light { position, intensity };
}

