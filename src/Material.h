//
// Created by sam on 8/15/24.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Color.h"
#include "Light.h"

struct Material {
    Color color;
    double ambient;
    double diffuse;
    double specular;
    double shininess;

    explicit Material(const Color &color = Color{1,1,1}, double ambient = 0.1, double diffuse = 0.9, double specular = 0.9, double shininess = 200.0);

    [[nodiscard]] Color lighting(const Light & light, const Point & p, const Vector & eyeV, const Vector & normalV) const;
};



#endif //MATERIAL_H
