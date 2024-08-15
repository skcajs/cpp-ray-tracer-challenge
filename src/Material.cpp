//
// Created by sam on 8/15/24.
//

#include "Material.h"

#include <cmath>

Material::Material(const Color &color, const float ambient, const float diffuse, const float specular, const float shininess) :
                                    color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}

Color Material::lighting(const Light &light, const Point &p, const Vector &eyeV, const Vector &normalV) const {
    auto iDiffuse = Color::black(), iSpecular = Color::black();

    const auto effectiveColor = color * light.intensity;
    const auto lightV = (light.position - p).normalize();
    const auto iAmbient = effectiveColor * ambient;

    if (const auto lightDotNormal = lightV.dot(normalV); lightDotNormal > 0) {
        iDiffuse = effectiveColor * diffuse * lightDotNormal;

        const auto reflectV = (lightV * -1).reflect(normalV);

        if (const auto reflectDotEye = reflectV.dot(eyeV); reflectDotEye > 0) {
            const auto factor = std::pow(reflectDotEye, shininess);
            iSpecular = light.intensity * specular * factor;
        }
    }
    return iAmbient + iDiffuse + iSpecular;
}
