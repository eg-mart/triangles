#include <gtest/gtest.h>

#include "triangle.h"
#include "vector3.h"

using namespace geometry;

class PointOnTriangle : public testing::Test {
protected:
    triangle_t t_simple = triangle_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0),
                                  vector3_t(0, 1, 0));

    vector3_t zero = vector3_t(0, 0, 0);
    vector3_t on_triangle = vector3_t(0.25, 0.25, 0);
    vector3_t outside_triangle1 = vector3_t(1, 1, 0);
    vector3_t outside_triangle2 = vector3_t(0, 0, 1);
};


TEST_F(PointOnTriangle, Trivial) {
    EXPECT_TRUE(t_simple.is_point_on_triangle(zero));
    EXPECT_TRUE(t_simple.is_point_on_triangle(on_triangle));
    EXPECT_FALSE(t_simple.is_point_on_triangle(outside_triangle1));
    EXPECT_FALSE(t_simple.is_point_on_triangle(outside_triangle2));
}

TEST_F(PointOnTriangle, Edge) {

}

TEST_F(PointOnTriangle, Complex) {

}

TEST_F(PointOnTriangle, Degenerate) {

}

TEST(TriangleIntersect, Classic) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t2 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(1, 1, 1),
                               vector3_t(1, 1, -2));
}
