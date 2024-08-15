//
// Created by sam on 8/15/24.
//

#include "test.h"

TEST_CASE("The default material") {
    const auto m = Material {};
    REQUIRE_COLORS(m.color, color(1,1,1));
    REQUIRE(m.ambient == 0.1f);
    REQUIRE(m.diffuse == 0.9f);
    REQUIRE(m.specular == 0.9f);
    REQUIRE(m.shininess == 200.0f);
}
