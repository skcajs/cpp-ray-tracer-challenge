//
// Created by sam on 8/15/24.
//

#ifndef LIGHT_H
#define LIGHT_H
#include "Color.h"
#include "Tuple.h"


class Light {
public:
    Point position;
    Color intensity;
    Light(const Point& position, const Color& intensity);
};

Light pointLight(const Point &position, const Color &intensity);



#endif //LIGHT_H
