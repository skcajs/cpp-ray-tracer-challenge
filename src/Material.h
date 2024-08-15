//
// Created by sam on 8/15/24.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Color.h"
#include "Light.h"

struct Material {
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;

    explicit Material(const Color &color = Color{1,1,1}, float ambient = 0.1, float diffuse = 0.9, float specular = 0.9, float shininess = 200.0);

    [[nodiscard]] Color lighting(const Light & light, const Point & p, const Vector & eyeV, const Vector & normalV) const;
};



#endif //MATERIAL_H
