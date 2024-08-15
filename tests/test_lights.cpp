//
// Created by sam on 8/15/24.
//

#include "test.h"

TEST_CASE("A point light has a position and intensity") {
    const auto intensity = color(1,1,1);
    const auto position = point(0,0,0);
    const auto light = pointLight(position, intensity);
    REQUIRE_TUPLES(light.position, position);
    REQUIRE_COLORS(light.intensity, intensity);
}