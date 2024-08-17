//
// Created by sam on 8/13/24.
//

#include "Canvas.h"
#include "Interval.h"
#include <X11/Xlib.h>
#include <format>
#include <cstdlib>
#include <iostream>

Canvas::Canvas(const int width, const int height)
    : mWidth(width), mHeight(height), image(height, std::vector<Color>(width, Color::blue())) {}

void Canvas::setImage(const std::vector<std::vector<Color>>& nextImage) {
    image = nextImage;
}

void Canvas::setPixel(int x, int y, const Color& color) {
    // Update the internal image data
    image[y][x] = color;

    // Open connection to X server
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        fprintf(stderr, "Unable to open X display\n");
        exit(1);
    }

    // Get default screen
    const int screen = DefaultScreen(display);

    // Create a window (if needed, this should be done only once)
    const Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, mWidth, mHeight, 1,
                                              BlackPixel(display, screen), WhitePixel(display, screen));

    // Create an XImage to hold the image data
    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen),
                                  ZPixmap, 0, nullptr, mWidth, mHeight, 32, 0);

    if (!ximage) {
        fprintf(stderr, "Unable to create XImage\n");
        XCloseDisplay(display);
        exit(1);
    }

    // Allocate memory for the image data (if needed, should be done once)
    ximage->data = static_cast<char *>(malloc(ximage->bytes_per_line * mHeight));

    // Set the pixel color in XImage
    const auto r = std::min(1.0, std::max(0.0, linear_to_gamma(color.r)));
    const auto g = std::min(1.0, std::max(0.0, linear_to_gamma(color.g)));
    const auto b = std::min(1.0, std::max(0.0, linear_to_gamma(color.b)));

    const unsigned long pixel = (static_cast<unsigned long>(r * 255) << 16) |
                                (static_cast<unsigned long>(g * 255) << 8) |
                                static_cast<unsigned long>(b * 255);

    const int byte_offset = y * ximage->bytes_per_line + x * (ximage->bits_per_pixel / 8);
    const auto pixel_ptr = reinterpret_cast<unsigned long *>(ximage->data + byte_offset);
    *pixel_ptr = pixel;

    // Draw the image to the window
    GC gc = XCreateGC(display, window, 0, nullptr);
    XPutImage(display, window, gc, ximage, 0, 0, 0, 0, mWidth, mHeight);

    // Free resources
    XFreeGC(display, gc);
    XFree(ximage);
    XCloseDisplay(display);
}

void Canvas::display() const {
    XEvent event;

    // Open connection to X server
    Display *display = XOpenDisplay(nullptr);
    if (display == nullptr) {
        fprintf(stderr, "Unable to open X display\n");
        exit(1);
    }

    // Get default screen
    const int screen = DefaultScreen(display);

    // Create a window
    const Window window = XCreateSimpleWindow(display, RootWindow(display, screen), 10, 10, mWidth, mHeight, 1,
                                              BlackPixel(display, screen), WhitePixel(display, screen));

    // Select input events we are interested in
    XSelectInput(display, window, ExposureMask | KeyPressMask);

    // Map (show) the window
    XMapWindow(display, window);

    // Create an XImage to hold the image data
    XImage *ximage = XCreateImage(display, DefaultVisual(display, screen), DefaultDepth(display, screen),
                                  ZPixmap, 0, nullptr, mWidth, mHeight, 32, 0);

    if (!ximage) {
        fprintf(stderr, "Unable to create XImage\n");
        XCloseDisplay(display);
        exit(1);
    }

    // Allocate memory for the image data
    ximage->data = static_cast<char *>(malloc(ximage->bytes_per_line * mHeight));

    // Copy canvas data to the XImage
    for (int y = 0; y < mHeight; y++) {
        for (int x = 0; x < mWidth; x++) {
            const Color& color = image[y][x];

            // Clamp to the range [0, 1]
            const auto r = std::min(1.0, std::max(0.0, linear_to_gamma(color.r)));
            const auto g = std::min(1.0, std::max(0.0, linear_to_gamma(color.g)));
            const auto b = std::min(1.0, std::max(0.0, linear_to_gamma(color.b)));

            // Convert to 8-bit integer values
            const unsigned long pixel = (static_cast<unsigned long>(r * 255) << 16) |
                                        (static_cast<unsigned long>(g * 255) << 8) |
                                        static_cast<unsigned long>(b * 255);

            // Calculate the position in the data buffer
            const int byte_offset = y * ximage->bytes_per_line + x * (ximage->bits_per_pixel / 8);

            // Assuming 32-bit color depth
            const auto pixel_ptr = reinterpret_cast<unsigned long *>(ximage->data + byte_offset);
            *pixel_ptr = pixel;
        }
    }

    // Event loop
    while (true) {
        XNextEvent(display, &event);

        // Draw or redraw the window when it is exposed
        if (event.type == Expose) {
            GC gc = XCreateGC(display, window, 0, nullptr);

            // Draw the image to the window
            XPutImage(display, window, gc, ximage, 0, 0, 0, 0, mWidth, mHeight);

            XFreeGC(display, gc);
        }

        // Break the loop if a key is pressed
        if (event.type == KeyPress)
            break;
    }

    // Clean up
    XFree(ximage);
    XCloseDisplay(display);
}

void Canvas::display(const std::vector<std::vector<Color>> &nextImage) {
    setImage(nextImage);
    display();
}

void Canvas::write_color(std::ostream& out, const Color& pixel_color) {
    auto r = pixel_color.r;
    auto g = pixel_color.g;
    auto b = pixel_color.b;

    // Apply a linear to gamma transform for gamma 2
    r = linear_to_gamma(r);
    g = linear_to_gamma(g);
    b = linear_to_gamma(b);

    // Translate the [0,1] component values to the byte range [0,255].
    static const Interval intensity(0.000, 0.999);
    const int rbyte = static_cast<int>(256 * intensity.clamp(r));
    const int gbyte = static_cast<int>(256 * intensity.clamp(g));
    const int bbyte = static_cast<int>(256 * intensity.clamp(b));
}

#include "Canvas.h"
