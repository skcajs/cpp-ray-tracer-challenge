#ifndef COLOR_H
#define COLOR_H

#include <array>

class Color {
public:
    double e[4];

    // Constructor
    Color(double e0, double e1, double e2, double e3 = 1);

    // Accessors
    double r;
    double g;
    double b;
    double a;

    // Member functions
    Color operator-() const;
    Color& operator+=(const Color& v);
    Color& operator-=(const Color& v);
    Color& operator*=(double t);
    Color& operator/=(double t);

    [[nodiscard]] std::array<int, 4> RGB() const;
    Color operator*(double t) const;
    Color operator*(Color v) const;
    Color operator/(double t) const;

    // Static member function
    static Color black();
    static Color red();
    static Color green();
    static Color blue();
    static Color white();
};

// Non-member functions
Color color(double r, double g, double b);
Color operator+(const Color& u, const Color& v);
Color operator-(const Color& u, const Color& v);

#endif // COLOR_H