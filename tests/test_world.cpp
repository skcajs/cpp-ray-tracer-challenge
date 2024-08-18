//
// Created by sam on 8/18/24.
//

#include "test.h"


TEST_CASE("Creating a world") {
    const auto w = World {};
    REQUIRE(w.objects.empty());
    REQUIRE_FALSE(w.light.has_value());
}

TEST_CASE("The default world") {

    Sphere s1 {};
    Sphere s2 {};

    std::vector<Sphere> objects;
    objects.emplace_back(s1);
    objects.emplace_back(s2);

    // const auto w = defaultWorld();
    // REQUIRE(w.objects.empty());
    // REQUIRE_FALSE(w.light.has_value());
}
