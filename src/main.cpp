#include "Canvas.h"
#include "Sphere.h"

int main() {
    const auto rayOrigin = point(0,0,-5);
    constexpr auto wallSize = 7.0;
    constexpr auto canvasPixels = 512;
    constexpr auto pixelSize = wallSize/ canvasPixels;
    constexpr auto half = wallSize/ 2.0;

    const auto black = Color::black();
    auto shape = Sphere();
    shape.material = Material {};
    shape.material.color = color(1, 0.2, 1);

    const auto lightPosition = point(-10, 10, -10);
    const auto lightColor = color(1,1,1);
    const auto light = pointLight(lightPosition, lightColor);


    std::vector<std::vector<Color>> image(canvasPixels, std::vector<Color>(canvasPixels, Color::black()));
    auto canvas = Canvas {canvasPixels, canvasPixels};

    for (int y = 0; y < canvasPixels; ++y) {
        for (int x = 0; x < canvasPixels; ++x) {
            const auto position = point(-half + pixelSize * x, half - pixelSize * y, 10.0);
            const auto r = Ray {rayOrigin, (position-rayOrigin).normalize() };

            const auto xs = shape.intersect(r);
            if (const auto hit = xs.hit(); hit.has_value()) {
                auto it = *hit;
                const auto p = r.position(it.t);
                const auto normal = it.object->normalAt(p);
                const auto eye = -r.direction;
                // canvas.setPixel(x, y, it.object->material.lighting(light, p, eye, normal));
                image[y][x] = it.object->material.lighting(light, p, eye, normal);
                continue;
            }
            // canvas.setPixel(x,y, black);
            image[y][x] = black;
        }
    }
    canvas.display(image);

    return 0;
}
