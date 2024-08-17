//
// Created by sam on 8/13/24.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <cmath>
#include <string>
#include <vector>
#include "Color.h"

class Canvas {
public:
    int mWidth;
    int mHeight;
    std::vector<std::vector<Color>> image;

    explicit Canvas(int width = 100, int height = 100);

    void setImage(const std::vector<std::vector<Color>>& nextImage);
    void setPixel(int x, int y, const Color& color);

    void display() const;
    void display(const std::vector<std::vector<Color>>& nextImage);

    static void write_color(std::ostream& out, const Color& pixel_color);
};

inline double linear_to_gamma(const double linear_component) {
    if (linear_component > 0)
        return std::sqrt(linear_component);
    return 0;
}

#endif //CANVAS_H
