//
// Created by sam on 8/13/24.
//

#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <vector>
#include "Color.h"

class Canvas {
public:
    int mWidth;
    int mHeight;
    mutable std::vector<std::vector<Color>> image;

    explicit Canvas(int width = 100, int height = 100);

    void setImage(const std::vector<std::vector<Color>>& nextImage) const;
    void display() const;
    [[nodiscard]] std::string toPPM() const;
};

#endif //CANVAS_H
