//
// Created by sam on 8/15/24.
//

#include "Material.h"

#include <cmath>

Material::Material(const Color &color, const double ambient, const double diffuse, const double specular, const double shininess) :
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

bool operator==(const Material &lhs, const Material &rhs) {
    return lhs.ambient == rhs.ambient && lhs.diffuse == rhs.diffuse && lhs.shininess == rhs.shininess && lhs.specular == rhs.specular && lhs.color == rhs.color;
}
