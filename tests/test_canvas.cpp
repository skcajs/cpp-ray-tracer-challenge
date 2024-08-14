//
// Created by sam on 8/13/24.
//

#include "test.h"

TEST_CASE("Creating a canvas", "[create]") {
    const auto c = Canvas {10, 20};
    REQUIRE(c.mWidth == 10);
    REQUIRE(c.mHeight == 20);
}
