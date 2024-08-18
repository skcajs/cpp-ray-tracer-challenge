//
// Created by sam on 8/15/24.
//

#include "test.h"

TEST_CASE("The default material") {
    const auto m = Material {};
    COMPARE_COLORS(m.color, color(1,1,1));
    REQUIRE(m.ambient == 0.1);
    REQUIRE(m.diffuse == 0.9);
    REQUIRE(m.specular == 0.9);
    REQUIRE(m.shininess == 200.0);
}

TEST_CASE("Lighting with the eye between the light and the surface") {
    const auto m = Material {};
    const auto position = point(0,0,0);

    const auto eyeV = vector(0,0,-1);
    const auto normalV = vector(0,0,-1);
    const auto light = pointLight(point(0,0,-10), color(1,1,1));
    const auto result = m.lighting(light, position, eyeV, normalV);
    COMPARE_COLORS(result, color(1.9,1.9,1.9));
}

TEST_CASE("Lighting with the eye between the light and the surface, eye offset 45") {
    const auto m = Material {};
    const auto position = point(0,0,0);

    constexpr auto root = std::sqrt(2)/2.0;
    const auto eyeV = vector(root,root,root);
    const auto normalV = vector(0,0,-1);
    const auto light = pointLight(point(0,0,-10), color(1,1,1));
    const auto result = m.lighting(light, position, eyeV, normalV);
    COMPARE_COLORS(result, color(1.0,1.0,1.0));
}

TEST_CASE("Lighting with the eye opposite the surface, light offset 45") {
    const auto m = Material {};
    const auto position = point(0,0,0);

    constexpr auto n = 0.7364;
    const auto eyeV = vector(0,0,-1);
    const auto normalV = vector(0,0,-1);
    const auto light = pointLight(point(0,10,-10), color(1,1,1));
    const auto result = m.lighting(light, position, eyeV, normalV);
    COMPARE_COLORS(result, color(n,n,n));
}

TEST_CASE("Lighting with the eye in the path of the reflection vector") {
    const auto m = Material {};
    const auto position = point(0,0,0);

    constexpr auto n = 1.6364;
    constexpr auto root = std::sqrt(2)/2.0;
    const auto eyeV = vector(0,-root,-root);
    const auto normalV = vector(0,0,-1);
    const auto light = pointLight(point(0,10,-10), color(1,1,1));
    const auto result = m.lighting(light, position, eyeV, normalV);
    COMPARE_COLORS(result, color(n,n,n));
}

TEST_CASE("Lighting with the light behind the surface") {
    const auto m = Material {};
    const auto position = point(0,0,0);

    constexpr auto n = 0.1;
    const auto eyeV = vector(0,0,-1);
    const auto normalV = vector(0,0,-1);
    const auto light = pointLight(point(0,0,10), color(1,1,1));
    const auto result = m.lighting(light, position, eyeV, normalV);
    COMPARE_COLORS(result, color(n,n,n));
}