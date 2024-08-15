#include "Canvas.h"
#include "Sphere.h"

int main() {
    const auto rayOrigin = point(0,0,-5);
    constexpr auto wallSize = 7.0;
    constexpr auto canvasPixels = 512;
    constexpr auto pixelSize = wallSize/ canvasPixels;
    constexpr auto half = wallSize/ 2.0;

    const auto red = Color::red();
    const auto black = Color::black();
    const auto shape = Sphere();

    std::vector<std::vector<Color>> image(canvasPixels, std::vector<Color>(canvasPixels, Color::black()));

    const auto canvas = Canvas {canvasPixels, canvasPixels};

    for (int y = 0; y < canvasPixels; ++y) {
        const auto worldY = half - pixelSize * y;
        for (int x = 0; x < canvasPixels; ++x) {
            constexpr auto wallZ = 10.0;
            const auto worldX = -half + pixelSize * x;
            const auto position = point(worldX, worldY, wallZ);
            const auto r = Ray {rayOrigin, (position-rayOrigin).normalize() };
            if (const auto xs = shape.intersect(r); xs.hit().has_value()) {
                image[x][y] = red;
                continue;
            }
            image[x][y] = black;
        }
    }

    canvas.setImage(image);
    canvas.display();

    return 0;
}
