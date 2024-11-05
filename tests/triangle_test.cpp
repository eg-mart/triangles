#include <gtest/gtest.h>

#include "triangle.h"
#include "vector3.h"

using namespace geometry;

TEST(PointOnTriangle, Trivial) {
    triangle_t t = triangle_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0),
                                  vector3_t(0, 1, 0)); 
    vector3_t zero = vector3_t(0, 0, 0);
    vector3_t on_triangle = vector3_t(0.5, 0.5, 0);
    vector3_t outside_triangle1 = vector3_t(1, 1, 0);
    vector3_t outside_triangle2 = vector3_t(0, 0, 1);

    EXPECT_TRUE(t.is_point_on_triangle(zero));
    EXPECT_TRUE(t.is_point_on_triangle(on_triangle));
    EXPECT_FALSE(t.is_point_on_triangle(outside_triangle1));
    EXPECT_FALSE(t.is_point_on_triangle(outside_triangle2));
}

TEST(PointOnTriangle, Edge) {

}

TEST(PointOnTriangle, Complex) {

}

TEST(PointOnTriangle, Degenerate) {

}
