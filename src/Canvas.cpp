//
// Created by sam on 8/13/24.
//

#include "Canvas.h"
#include <X11/Xlib.h>
#include <format>
#include <cstdlib> // For exit() and malloc()

Canvas::Canvas(const int width, const int height)
    : mWidth(width), mHeight(height), image(height, std::vector<Color>(width, Color::blue())) {}

void Canvas::setImage(const std::vector<std::vector<Color>>& nextImage) {
    image = nextImage;
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
            const unsigned long pixel = (static_cast<int>(color.r * 255) << 16) |
                                        (static_cast<int>(color.g * 255) << 8) |
                                        static_cast<int>(color.b * 255);

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

std::string Canvas::toPPM() const {
    std::string ppm;
    ppm.append("P3\n");
    ppm.append(std::format("{} {}\n", mWidth, mHeight));
    ppm.append("255\n");

    for (int j = 0; j < mHeight; j++) {
        for (int i = 0; i < mWidth; i++) {
            const auto r = static_cast<double>(i) / (mWidth - 1);
            const auto g = static_cast<double>(j) / (mHeight - 1);
            constexpr auto b = 0.0;

            int ir = static_cast<int>(255.999 * r);
            int ig = static_cast<int>(255.999 * g);
            int ib = static_cast<int>(255.999 * b);

            ppm.append(std::format("{} {} {}\n", ir, ig, ib));
        }
    }
    return ppm;
}

#include "Canvas.h"
