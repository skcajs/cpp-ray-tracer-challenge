cmake_minimum_required(VERSION 3.28)
project(cpp_ray_tracer_challenge)

set(CMAKE_CXX_STANDARD 23)

include(FetchContent)

# Fetch Catch2 library
FetchContent_Declare(
        catch
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.4.0  # You can specify the version here
)
FetchContent_MakeAvailable(catch)

# Find the X11 package
find_package(X11 REQUIRED)

# Main application target
add_executable(cpp_ray_tracer_challenge
        src/main.cpp
        src/Tuple.cpp
        src/Color.cpp
        src/Canvas.cpp
        src/Matrix.cpp
        src/Transformations.cpp
        src/Transformations.h
        src/Ray.cpp
        src/Ray.h
        src/Sphere.cpp
        src/Sphere.h
        src/Intersection.cpp
        src/Intersection.h
        src/Intersections.cpp
        src/Intersections.h
        src/Light.cpp
        src/Light.h
        src/Material.cpp
        src/Material.h
        src/Interval.h
        src/World.cpp
        src/World.h
        src/Computations.cpp
        src/Computations.h
)

# Include the X11 headers
target_include_directories(cpp_ray_tracer_challenge PRIVATE ${X11_INCLUDE_DIR})

# Link against the X11 libraries
target_link_libraries(cpp_ray_tracer_challenge PRIVATE ${X11_LIBRARIES})

# Separate test executable
add_executable(tests
        src/Canvas.cpp
        src/Color.cpp
        src/Matrix.cpp
        src/Tuple.cpp
        src/Transformations.cpp
        src/Ray.cpp
        src/Sphere.cpp
        src/Intersection.cpp
        src/Intersections.cpp
        src/Light.cpp
        src/Material.cpp
        src/World.cpp
        src/Computations.cpp

        tests/test_tuples.cpp
        tests/test_colors.cpp
        tests/test_canvas.cpp
        tests/test_matrix.cpp
        tests/test_transformations.cpp
        tests/test_ray.cpp
        tests/test_spheres.cpp
        tests/test_intersections.cpp
        tests/test_lights.cpp
        tests/test_materials.cpp
        tests/test_world.cpp
)

# Link Catch2 with the test executable
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain ${X11_LIBRARIES})

# Enable testing with CTest
include(CTest)
add_test(NAME tests COMMAND tests)