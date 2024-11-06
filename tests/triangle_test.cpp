#include <gtest/gtest.h>

#include "triangle.h"
#include "vector3.h"

using namespace geometry;

class PointOnTriangle : public testing::Test {
protected:
    triangle_t t_simple = triangle_t(vector3_t(0, 0, 0), 
                                     vector3_t(1, 0, 0),
                                     vector3_t(0, 1, 0));

    vector3_t zero = vector3_t(0, 0, 0);
};


TEST_F(PointOnTriangle, Trivial) {
    vector3_t in_triangle       = vector3_t(0.25, 0.25, 0);
    vector3_t outside_triangle1 = vector3_t(1, 1, 0);
    vector3_t outside_triangle2 = vector3_t(0, 0, 1);

    EXPECT_TRUE(t_simple.is_point_on_triangle(zero));
    EXPECT_TRUE(t_simple.is_point_on_triangle(in_triangle));
    EXPECT_FALSE(t_simple.is_point_on_triangle(outside_triangle1));
    EXPECT_FALSE(t_simple.is_point_on_triangle(outside_triangle2));
}

TEST_F(PointOnTriangle, Edge) {
    EXPECT_TRUE(t_simple.is_point_on_triangle(zero));
    EXPECT_TRUE(t_simple.is_point_on_triangle(vector3_t(1, 0, 0)));
    EXPECT_TRUE(t_simple.is_point_on_triangle(vector3_t(0, 1, 0)));
    EXPECT_TRUE(t_simple.is_point_on_triangle(vector3_t(0.5, 0, 0)));
    EXPECT_TRUE(t_simple.is_point_on_triangle(vector3_t(0, 0.5, 0)));
    EXPECT_TRUE(t_simple.is_point_on_triangle(vector3_t(0.5, 0.5, 0)));
    EXPECT_FALSE(t_simple.is_point_on_triangle(vector3_t(1.5, 0, 0)));
    EXPECT_FALSE(t_simple.is_point_on_triangle(vector3_t(0, 1.5, 0)));
}

TEST_F(PointOnTriangle, Complex) {

}

TEST_F(PointOnTriangle, Degenerate) {
    triangle_t t_degenerate_segment_1 = triangle_t(vector3_t(0, 0, 0), 
                                                   vector3_t(1, 0, 0),
                                                   vector3_t(2, 0, 0));
                                    
    triangle_t t_degenerate_segment_2 = triangle_t(vector3_t(0, 0, 0), 
                                                   vector3_t(0, 0, 0),
                                                   vector3_t(1, 0, 0));

    triangle_t t_degenerate_point     = triangle_t(vector3_t(0, 0, 0), 
                                                   vector3_t(0, 0, 0),
                                                   vector3_t(0, 0, 0));

    EXPECT_TRUE(t_degenerate_point.is_point_on_triangle(zero));
    EXPECT_FALSE(t_degenerate_point.is_point_on_triangle(vector3_t(1, 0, 0)));

    EXPECT_TRUE(t_degenerate_segment_1.is_point_on_triangle(zero));
    EXPECT_TRUE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(2, 0, 0)));
    EXPECT_TRUE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(1, 0, 0)));
    EXPECT_TRUE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(0.5, 0, 0)));
    EXPECT_TRUE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(1.5, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(2.1, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(-0.1, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_1.is_point_on_triangle(vector3_t(1, 0.1, 0)));

    EXPECT_TRUE(t_degenerate_segment_2.is_point_on_triangle(zero));
    EXPECT_TRUE(t_degenerate_segment_2.is_point_on_triangle(vector3_t(1, 0, 0)));
    EXPECT_TRUE(t_degenerate_segment_2.is_point_on_triangle(vector3_t(0.5, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_2.is_point_on_triangle(vector3_t(1.1, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_2.is_point_on_triangle(vector3_t(-0.1, 0, 0)));
    EXPECT_FALSE(t_degenerate_segment_2.is_point_on_triangle(vector3_t(0.5, 0.1, 0)));
}

TEST(TriangleIntersect, Classic) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t2 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(1, 1, 1),
                               vector3_t(1, 1, -2));

    triangle_t t3 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(1, 1, 1),
                               vector3_t(1, 1, 0));

    EXPECT_TRUE(t1.is_intersecting(t2));
    EXPECT_FALSE(t1.is_intersecting(t3));
}

TEST(TriangleIntersect, Pierce) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t2 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0.5, 0.5, 1),
                               vector3_t(0.25, 0.25, -2));

    triangle_t t3 = triangle_t(vector3_t(0.5, 1, -1), 
                               vector3_t(0.5, 1, 1),
                               vector3_t(0.5, -1, 0));

    triangle_t t4 = triangle_t(vector3_t(1.5, 0, -1), 
                               vector3_t(0, 1.5, -1),
                               vector3_t(1.5, 1.5, 1));

    triangle_t t5 = triangle_t(vector3_t(1.5, 0, -1), 
                               vector3_t(0, 1.5, -1),
                               vector3_t(1.2, 1.2, 1));

    EXPECT_TRUE(t1.is_intersecting(t2));
    EXPECT_TRUE(t1.is_intersecting(t3));
    EXPECT_FALSE(t1.is_intersecting(t4));
    EXPECT_FALSE(t1.is_intersecting(t5));
}

TEST(TriangleIntersect, SegmentOnPlane) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t2 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0.5, 0, 0),
                               vector3_t(0, 0.5, 0));

    triangle_t t3 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0.5, 0, 0),
                               vector3_t(1.5, 0, 0));

    triangle_t t4 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0, 2, 0),
                               vector3_t(2, 0, 0));

    triangle_t t5 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0, 0, 0),
                               vector3_t(0.5, 0.5, 0));

    triangle_t t6 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0, -1, 0),
                               vector3_t(1, 2, 0));

    triangle_t t7 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0, 2, 0),
                               vector3_t(2.1, 0, 0));
                               
    triangle_t t8 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0.5, 0.5, 0),
                               vector3_t(1, 1, 0));

    triangle_t t9 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(0.51, 0.51, 0),
                               vector3_t(1, 1, 0));

    EXPECT_TRUE(t1.is_intersecting(t2));
    EXPECT_TRUE(t1.is_intersecting(t3));
    EXPECT_FALSE(t1.is_intersecting(t4));
    EXPECT_TRUE(t1.is_intersecting(t5));
    EXPECT_TRUE(t1.is_intersecting(t6));
    EXPECT_FALSE(t1.is_intersecting(t7));
    EXPECT_TRUE(t1.is_intersecting(t8));
    EXPECT_FALSE(t1.is_intersecting(t9));
}
