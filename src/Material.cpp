//
// Created by sam on 8/15/24.
//

#include "Material.h"

Material::Material(const Color &color, const float ambient, const float diffuse, const float specular, const float shininess) :
                                    color(color), ambient(ambient), diffuse(diffuse), specular(specular), shininess(shininess) {}
