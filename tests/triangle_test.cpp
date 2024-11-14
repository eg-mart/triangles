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

    triangle_t t_paral = triangle_t(vector3_t(0, 0, 1), 
                                    vector3_t(1, 0, 1),
                                    vector3_t(0, 1, 1));

    triangle_t t4 = triangle_t(vector3_t(0, 0, 1), 
                               vector3_t(1, 0, -1),
                               vector3_t(0, 1, -1));

    EXPECT_TRUE(t1.is_intersecting(t2));
    EXPECT_FALSE(t1.is_intersecting(t3));
    EXPECT_FALSE(t1.is_intersecting(t_paral));
    EXPECT_TRUE(t1.is_intersecting(t4));
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

TEST(TriangleIntersect, OneTriangleDegenerateToSegmentPointsCoinsidence) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_3 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1, 1, 1));

    triangle_t t_4 = triangle_t(vector3_t(0.2, 0.2, 0), 
                                vector3_t(0.2, 0.2, 0),
                                vector3_t(1, 1, 1));

    triangle_t t_5 = triangle_t(vector3_t(0.5, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_6 = triangle_t(vector3_t(0.5, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_7 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                vector3_t(0.5, 0.5, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_8 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                vector3_t(0.5, 0.5, 0),
                                vector3_t(1.5, -0.5, 0));

    triangle_t t_9 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                vector3_t(0.5, 0.5, 0),
                                vector3_t(1, 0, 1));

    triangle_t t_10 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_11 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_12 = triangle_t(vector3_t(0.2, 0.2, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_13 = triangle_t(vector3_t(0.5, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_14 = triangle_t(vector3_t(0.5, 0, 0), 
                                 vector3_t(2, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_15 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_16 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                 vector3_t(1.5, -0.5, 0),
                                 vector3_t(1.5, -0.5, 0));

    triangle_t t_17 = triangle_t(vector3_t(0.5, 0.5, 0), 
                                 vector3_t(1, 0, 1),
                                 vector3_t(1, 0, 1));

    triangle_t t_18 = triangle_t(vector3_t(-0.5, -0.5, 0), 
                                 vector3_t(-0.5, -0.5, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_19 = triangle_t(vector3_t(-0.5, -0.5, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_20 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(0, 0, 1),
                                 vector3_t(1, 0, 1));

    triangle_t t_21 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(0, 0, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_22 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(0, 0, 1),
                                 vector3_t(0.6, 0.6, 0));

    triangle_t t_23 = triangle_t(vector3_t(1.1, 0, 0), 
                                 vector3_t(1.1, 0, 0),
                                 vector3_t(0, 1.1, 0));

    triangle_t t_24 = triangle_t(vector3_t(-0.1, -0.1, 0), 
                                 vector3_t(-0.1, -0.1, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_25 = triangle_t(vector3_t(3, 0, 0), 
                                 vector3_t(3, 0, 0),
                                 vector3_t(0, 1.1, 0));

    triangle_t t_26 = triangle_t(vector3_t(1.1, 0, 0), 
                                 vector3_t(1.1, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_27 = triangle_t(vector3_t(-0.5, -0.5, 0), 
                                 vector3_t(-0.5, -0.5, 0),
                                 vector3_t(1, 1, 0.1));

    triangle_t t_28 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(1, 0, 1),
                                 vector3_t(1, 0, 1));

    triangle_t t_29 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_30 = triangle_t(vector3_t(0, 0, 1), 
                                 vector3_t(0.6, 0.6, 0),
                                 vector3_t(0.6, 0.6, 0));

    triangle_t t_31 = triangle_t(vector3_t(1.1, 0, 0), 
                                 vector3_t(0, 1.1, 0),
                                 vector3_t(0, 1.1, 0));

    triangle_t t_32 = triangle_t(vector3_t(-0.1, -0.1, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_33 = triangle_t(vector3_t(3, 0, 0), 
                                 vector3_t(0, 1.1, 0),
                                 vector3_t(0, 1.1, 0));

    triangle_t t_34 = triangle_t(vector3_t(1.1, 0, 0), 
                                 vector3_t(2, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_35 = triangle_t(vector3_t(-0.5, -0.5, 0), 
                                 vector3_t(1, 1, 0.1),
                                 vector3_t(1, 1, 0.1));

    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_TRUE(t1.is_intersecting(t_3));
    EXPECT_TRUE(t1.is_intersecting(t_4));
    EXPECT_TRUE(t1.is_intersecting(t_5));
    EXPECT_TRUE(t1.is_intersecting(t_6));
    EXPECT_TRUE(t1.is_intersecting(t_7));
    EXPECT_TRUE(t1.is_intersecting(t_8));
    EXPECT_TRUE(t1.is_intersecting(t_9));
    EXPECT_TRUE(t1.is_intersecting(t_10));
    EXPECT_TRUE(t1.is_intersecting(t_11));
    EXPECT_TRUE(t1.is_intersecting(t_12));
    EXPECT_TRUE(t1.is_intersecting(t_13));
    EXPECT_TRUE(t1.is_intersecting(t_14));
    EXPECT_TRUE(t1.is_intersecting(t_15));
    EXPECT_TRUE(t1.is_intersecting(t_16));
    EXPECT_TRUE(t1.is_intersecting(t_17));
    EXPECT_TRUE(t1.is_intersecting(t_18));
    EXPECT_TRUE(t1.is_intersecting(t_19));
    EXPECT_FALSE(t1.is_intersecting(t_20));
    EXPECT_FALSE(t1.is_intersecting(t_21));
    EXPECT_FALSE(t1.is_intersecting(t_22));
    EXPECT_FALSE(t1.is_intersecting(t_23));
    EXPECT_FALSE(t1.is_intersecting(t_24));
    EXPECT_FALSE(t1.is_intersecting(t_25));
    EXPECT_FALSE(t1.is_intersecting(t_26));
    EXPECT_FALSE(t1.is_intersecting(t_27));
    EXPECT_FALSE(t1.is_intersecting(t_28));
    EXPECT_FALSE(t1.is_intersecting(t_29));
    EXPECT_FALSE(t1.is_intersecting(t_30));
    EXPECT_FALSE(t1.is_intersecting(t_31));
    EXPECT_FALSE(t1.is_intersecting(t_32));
    EXPECT_FALSE(t1.is_intersecting(t_33));
    EXPECT_FALSE(t1.is_intersecting(t_34));
    EXPECT_FALSE(t1.is_intersecting(t_35));
}

TEST(TriangleIntersect, OneTriangleDegenerateToSegmentPointsNotCoinsidence) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_3 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1.1, 0, 0));

    triangle_t t_4 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(1, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_5 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(1.1, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_6 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_7 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1.1, 0, 0));

    triangle_t t_8 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(1, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_9 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(1.1, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_10 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.5, 0.5, 0));

    triangle_t t_11 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.1, 0.6, 0));

    triangle_t t_12 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0.5, 0.5, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_13 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0.6, 0.6, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_14 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.3, 0.2, 0),
                                 vector3_t(0.6, 0.5, 0));

    triangle_t t_15 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.6, 0.6, 0));

    triangle_t t_16 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.5, 0.5, 0),
                                 vector3_t(0.9, 1, 0));

    triangle_t t_17 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.6, 0.6, 0),
                                 vector3_t(1.1, 1.2, 0));

    triangle_t t_18 = triangle_t(vector3_t(0.1, 0.1, 0), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.5, 0.5, 0));

    triangle_t t_19 = triangle_t(vector3_t(0.1, 0.1, 0), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.6, 0.6, 0));

    triangle_t t_20 = triangle_t(vector3_t(0.1, 0.1, 0), 
                                 vector3_t(0.5, 0.5, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_21 = triangle_t(vector3_t(0.1, 0.1, 0), 
                                 vector3_t(0.6, 0.6, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_22 = triangle_t(vector3_t(0.1, 0.1, -0.1), 
                                 vector3_t(0.2, 0.2, 0),
                                 vector3_t(0.3, 0.3, 0.1));

    triangle_t t_23 = triangle_t(vector3_t(0.1, 0.1, -0.2), 
                                 vector3_t(0.2, 0.2, -0.1),
                                 vector3_t(0.4, 0.4, 0.1));

    triangle_t t_24 = triangle_t(vector3_t(0.1, 0.1, -0.1), 
                                 vector3_t(0.2, 0.2, 0.1),
                                 vector3_t(0.3, 0.3, 0.3));

    triangle_t t_26 = triangle_t(vector3_t(-0.1, -0.1, -0.1), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(0.1, 0.1, 0.1));

    triangle_t t_27 = triangle_t(vector3_t(-0.2, -0.2, -0.2), 
                                 vector3_t(-0.1, -0.1, -0.1),
                                 vector3_t(0.1, 0.1, 0.1));

    triangle_t t_28 = triangle_t(vector3_t(-0.2, 0, -0.2), 
                                 vector3_t(-0.1, 0, -0.1),
                                 vector3_t(0.1, 0, 0.1));

    triangle_t t_29 = triangle_t(vector3_t(-0.1, 0, -0.1), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(0.1, 0, 0.1));

    triangle_t t_30 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0.5, 0),
                                 vector3_t(-0.1, 0.1, 0));

    triangle_t t_31 = triangle_t(vector3_t(0, 0, 0.1), 
                                 vector3_t(0.2, 0.2, 0.1),
                                 vector3_t(0.5, 0.5, 0.1));

    triangle_t t_32 = triangle_t(vector3_t(0, 0, 0.1), 
                                 vector3_t(0.2, 0.2, 0.2),
                                 vector3_t(0.5, 0.5, 0.3));

    triangle_t t_33 = triangle_t(vector3_t(-0.1, 0, -0.1), 
                                 vector3_t(-0.1, 0.5, 0),
                                 vector3_t(-0.1, 1, 0.1));

    triangle_t t_34 = triangle_t(vector3_t(-0.6, 0, -0.5), 
                                 vector3_t(-0.1, 0.5, 0),
                                 vector3_t(0.4, 1, 0.5));

    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_TRUE(t1.is_intersecting(t_3));
    EXPECT_TRUE(t1.is_intersecting(t_4));
    EXPECT_TRUE(t1.is_intersecting(t_5));
    EXPECT_TRUE(t1.is_intersecting(t_6));
    EXPECT_TRUE(t1.is_intersecting(t_7));
    EXPECT_TRUE(t1.is_intersecting(t_8));
    EXPECT_TRUE(t1.is_intersecting(t_9));
    EXPECT_TRUE(t1.is_intersecting(t_10));
    EXPECT_TRUE(t1.is_intersecting(t_11));
    EXPECT_TRUE(t1.is_intersecting(t_12));
    EXPECT_TRUE(t1.is_intersecting(t_13));
    EXPECT_TRUE(t1.is_intersecting(t_14));
    EXPECT_TRUE(t1.is_intersecting(t_15));
    EXPECT_TRUE(t1.is_intersecting(t_16));
    EXPECT_TRUE(t1.is_intersecting(t_17));
    EXPECT_TRUE(t1.is_intersecting(t_18));
    EXPECT_TRUE(t1.is_intersecting(t_19));
    EXPECT_TRUE(t1.is_intersecting(t_20));
    EXPECT_TRUE(t1.is_intersecting(t_21));
    EXPECT_TRUE(t1.is_intersecting(t_22));
    EXPECT_TRUE(t1.is_intersecting(t_23));
    EXPECT_TRUE(t1.is_intersecting(t_24));
    EXPECT_TRUE(t1.is_intersecting(t_26));
    EXPECT_TRUE(t1.is_intersecting(t_27));
    EXPECT_TRUE(t1.is_intersecting(t_28));
    EXPECT_TRUE(t1.is_intersecting(t_29));
    EXPECT_FALSE(t1.is_intersecting(t_30));
    EXPECT_FALSE(t1.is_intersecting(t_31));
    EXPECT_FALSE(t1.is_intersecting(t_32));
    EXPECT_FALSE(t1.is_intersecting(t_33));
    EXPECT_FALSE(t1.is_intersecting(t_34));
}

TEST(TriangleIntersect, OneTriangleDegenerateToPoint) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(0, 1, 0));

    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(0, 0, 0));

    triangle_t t_3 = triangle_t(vector3_t(0.5, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(0.5, 0, 0));

    triangle_t t_4 = triangle_t(vector3_t(0.2, 0.2, 0), 
                                vector3_t(0.2, 0.2, 0),
                                vector3_t(0.2, 0.2, 0));

    triangle_t t_5 = triangle_t(vector3_t(0.2, 0.2, 0.1), 
                                vector3_t(0.2, 0.2, 0.1),
                                vector3_t(0.2, 0.2, 0.1));

    triangle_t t_6 = triangle_t(vector3_t(1.1, 0, 0), 
                                vector3_t(1.1, 0, 0),
                                vector3_t(1.1, 0, 0));

    triangle_t t_7 = triangle_t(vector3_t(0.6, 0.6, 0), 
                                vector3_t(0.6, 0.6, 0),
                                vector3_t(0.6, 0.6, 0));

    triangle_t t_8 = triangle_t(vector3_t(0, 0, 0.1), 
                                vector3_t(0, 0, 0.1),
                                vector3_t(0, 0, 0.1));

    triangle_t t_9 = triangle_t(vector3_t(-0.1, -0.1, 0), 
                                vector3_t(-0.1, -0.1, 0),
                                vector3_t(-0.1, -0.1, 0));
                                

    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_TRUE(t1.is_intersecting(t_3));
    EXPECT_TRUE(t1.is_intersecting(t_4));
    EXPECT_FALSE(t1.is_intersecting(t_5));
    EXPECT_FALSE(t1.is_intersecting(t_6));
    EXPECT_FALSE(t1.is_intersecting(t_7));
    EXPECT_FALSE(t1.is_intersecting(t_8));
    EXPECT_FALSE(t1.is_intersecting(t_9));
}

TEST(TriangleIntersect, BothTriangleDegenerateToSegmentPointsNotCoinsidence) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(2, 0, 0));

    triangle_t t2 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(2, 0, 0));
                                
    triangle_t t3 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(2.1, 0, 0));

    triangle_t t4 = triangle_t(vector3_t(-0.1, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(2.1, 0, 0));

    triangle_t t5 = triangle_t(vector3_t(-0.1, 0, 0), 
                               vector3_t(1.1, 0, 0),
                               vector3_t(2.1, 0, 0));

    triangle_t t6 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1.1, 0, 0),
                               vector3_t(2.1, 0, 0));

    triangle_t t7 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1.1, 0, 0),
                               vector3_t(2, 0, 0));

    triangle_t t8 = triangle_t(vector3_t(-0.1, 0, 0), 
                               vector3_t(1.1, 0, 0),
                               vector3_t(2, 0, 0));

    triangle_t t9 = triangle_t(vector3_t(-0.1, 0, 0), 
                               vector3_t(2.1, 0, 0),
                               vector3_t(3, 0, 0));

    triangle_t t10 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(2.1, 0, 0),
                                vector3_t(3, 0, 0));

    triangle_t t11 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(2.1, 0, 0),
                                vector3_t(3, 0, 0));

    triangle_t t12 = triangle_t(vector3_t(1, 0, 0), 
                                vector3_t(2.1, 0, 0),
                                vector3_t(3, 0, 0));

    triangle_t t13 = triangle_t(vector3_t(1.1, 0, 0), 
                                vector3_t(2.1, 0, 0),
                                vector3_t(3, 0, 0));

    triangle_t t14 = triangle_t(vector3_t(2, 0, 0), 
                                vector3_t(2.1, 0, 0),
                                vector3_t(3, 0, 0));

    triangle_t t15 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(1.1, 1, 0),
                                vector3_t(2.1, 2, 0));

    triangle_t t16 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(1, 1, 0),
                                vector3_t(2, 2, 0));

    triangle_t t17 = triangle_t(vector3_t(1, 0, 0), 
                                vector3_t(2, 1, 0),
                                vector3_t(3, 2, 0));

    triangle_t t18 = triangle_t(vector3_t(0, -0.5, 0), 
                                vector3_t(1, 0, 0),
                                vector3_t(2, 0.5, 0));

    triangle_t t19 = triangle_t(vector3_t(0, -0.5, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 0.5, 0));
 
    triangle_t t20 = triangle_t(vector3_t(0, -0.5, 0), 
                                vector3_t(0.5, 0.1, 0),
                                vector3_t(1, 0.7, 0));

    triangle_t t21 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(1.1, 1, 0.1),
                                vector3_t(2.1, 2, 0.2));

    triangle_t t22 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(1, 1, 0.1),
                                vector3_t(2, 2, 0.2));

    triangle_t t23 = triangle_t(vector3_t(1, 0, 0), 
                                vector3_t(2, 1, 0.1),
                                vector3_t(3, 2, 0.2));

    triangle_t t24 = triangle_t(vector3_t(0, -0.5, -0.1), 
                                vector3_t(1, 0, 0),
                                vector3_t(2, 0.5, 0.1));

    triangle_t t25 = triangle_t(vector3_t(0, -0.5, -0.1), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 0.5, 0.1));

    triangle_t t26 = triangle_t(vector3_t(0, -0.5, -0.5), 
                                vector3_t(0.5, 0.1, 0.1),
                                vector3_t(1, 0.7, 0.7));

    triangle_t t27 = triangle_t(vector3_t(2.1, 0, 0), 
                                vector3_t(3, 0, 0),
                                vector3_t(4, 0, 0));

    triangle_t t28 = triangle_t(vector3_t(0, 0.1, 0), 
                                vector3_t(1, 0.1, 0),
                                vector3_t(2, 0.1, 0));

    triangle_t t29 = triangle_t(vector3_t(0, 0.1, 0), 
                                vector3_t(1, 1.1, 0),
                                vector3_t(2, 2.1, 0));

    triangle_t t30 = triangle_t(vector3_t(0, -0.1, 0), 
                                vector3_t(1, 0.9, 1),
                                vector3_t(2, 1.9, 2));


    EXPECT_TRUE(t1.is_intersecting(t2));
    EXPECT_TRUE(t1.is_intersecting(t3));
    EXPECT_TRUE(t1.is_intersecting(t4));
    EXPECT_TRUE(t1.is_intersecting(t5));
    EXPECT_TRUE(t1.is_intersecting(t6));
    EXPECT_TRUE(t1.is_intersecting(t7));
    EXPECT_TRUE(t1.is_intersecting(t8));
    EXPECT_TRUE(t1.is_intersecting(t9));
    EXPECT_TRUE(t1.is_intersecting(t10));
    EXPECT_TRUE(t1.is_intersecting(t11));
    EXPECT_TRUE(t1.is_intersecting(t12));
    EXPECT_TRUE(t1.is_intersecting(t13));
    EXPECT_TRUE(t1.is_intersecting(t14));
    EXPECT_TRUE(t1.is_intersecting(t15));
    EXPECT_TRUE(t1.is_intersecting(t16));
    EXPECT_TRUE(t1.is_intersecting(t17));
    EXPECT_TRUE(t1.is_intersecting(t18));
    EXPECT_TRUE(t1.is_intersecting(t19));
    EXPECT_TRUE(t1.is_intersecting(t20));
    EXPECT_TRUE(t1.is_intersecting(t21));
    EXPECT_TRUE(t1.is_intersecting(t22));
    EXPECT_TRUE(t1.is_intersecting(t23));
    EXPECT_TRUE(t1.is_intersecting(t24));
    EXPECT_TRUE(t1.is_intersecting(t25));
    EXPECT_TRUE(t1.is_intersecting(t26));
    EXPECT_FALSE(t1.is_intersecting(t27));
    EXPECT_FALSE(t1.is_intersecting(t28));
    EXPECT_FALSE(t1.is_intersecting(t29));
    EXPECT_FALSE(t1.is_intersecting(t30));
}

TEST(TriangleIntersect, OneTriangleDegenerateToSegmentPointsNotCoinsidenceAnotherToSegmentPointsCoinsidence) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(1, 0, 0),
                               vector3_t(2, 0, 0));
                               
    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(0.5, 0, 0));

    triangle_t t_3 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_4 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1.5, 0, 0));

    triangle_t t_5 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(2, 0, 0));

    triangle_t t_6 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(2.1, 0, 0));

    triangle_t t_7 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.1, 0, 0),
                                vector3_t(0.5, 0, 0));

    triangle_t t_8 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.1, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_9 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.1, 0, 0),
                                vector3_t(1.5, 0, 0));

    triangle_t t_10 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.1, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_11 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(0.1, 0, 0),
                                 vector3_t(2.1, 0, 0));

    triangle_t t_12 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(0.5, 0, 0));

    triangle_t t_13 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_14 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(1.5, 0, 0));

    triangle_t t_15 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_16 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(2.1, 0, 0));

    triangle_t t_17 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_18 = triangle_t(vector3_t(0.5, 0, 0), 
                                 vector3_t(0.5, 0, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_19 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_20 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_21 = triangle_t(vector3_t(0.5, 0, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_22 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_23 = triangle_t(vector3_t(-1, -1, -1), 
                                 vector3_t(-1, -1, -1),
                                 vector3_t(1, 1, 1));

    triangle_t t_24 = triangle_t(vector3_t(-0.5, -1, -1), 
                                 vector3_t(1.5, 1, 1),
                                 vector3_t(1.5, 1, 1));

    triangle_t t_25 = triangle_t(vector3_t(-1, -1, -1), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_26 = triangle_t(vector3_t(-0.5, -1, -1), 
                                 vector3_t(1.5, 1, 1),
                                 vector3_t(1.5, 1, 1));

    triangle_t t_27 = triangle_t(vector3_t(0, 0, 0.1), 
                                 vector3_t(2, 0, 0.1),
                                 vector3_t(2, 0, 0.1));

    triangle_t t_28 = triangle_t(vector3_t(2.1, 0, 0), 
                                 vector3_t(3, 0, 0),
                                 vector3_t(3, 0, 0));
                                
    triangle_t t_29 = triangle_t(vector3_t(1, 0.5, 0.5), 
                                 vector3_t(2, 2, 2),
                                 vector3_t(2, 2, 2));

    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_TRUE(t1.is_intersecting(t_3));
    EXPECT_TRUE(t1.is_intersecting(t_4));
    EXPECT_TRUE(t1.is_intersecting(t_5));
    EXPECT_TRUE(t1.is_intersecting(t_6));
    EXPECT_TRUE(t1.is_intersecting(t_7));
    EXPECT_TRUE(t1.is_intersecting(t_8));
    EXPECT_TRUE(t1.is_intersecting(t_9));
    EXPECT_TRUE(t1.is_intersecting(t_10));
    EXPECT_TRUE(t1.is_intersecting(t_11));
    EXPECT_TRUE(t1.is_intersecting(t_12));
    EXPECT_TRUE(t1.is_intersecting(t_13));
    EXPECT_TRUE(t1.is_intersecting(t_14));
    EXPECT_TRUE(t1.is_intersecting(t_15));
    EXPECT_TRUE(t1.is_intersecting(t_16));
    EXPECT_TRUE(t1.is_intersecting(t_17));
    EXPECT_TRUE(t1.is_intersecting(t_18));
    EXPECT_TRUE(t1.is_intersecting(t_19));
    EXPECT_TRUE(t1.is_intersecting(t_20));
    EXPECT_TRUE(t1.is_intersecting(t_21));
    EXPECT_TRUE(t1.is_intersecting(t_22));
    EXPECT_TRUE(t1.is_intersecting(t_23));
    EXPECT_TRUE(t1.is_intersecting(t_24));
    EXPECT_TRUE(t1.is_intersecting(t_25));
    EXPECT_TRUE(t1.is_intersecting(t_26));
    EXPECT_FALSE(t1.is_intersecting(t_27));
    EXPECT_FALSE(t1.is_intersecting(t_28));
    EXPECT_FALSE(t1.is_intersecting(t_29));
}

TEST(TriangleIntersect, BothTriangleDegenerateToSegmentPointsCoinsidence) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(0, 0, 0),
                               vector3_t(1, 0, 0));

    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_3 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.1, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_4 = triangle_t(vector3_t(0.1, 0, 0), 
                                vector3_t(0.1, 0, 0),
                                vector3_t(1.1, 0, 0));

    triangle_t t_5 = triangle_t(vector3_t(-0.1, 0, 0), 
                                vector3_t(-0.1, 0, 0),
                                vector3_t(1, 0, 0));

    triangle_t t_6 = triangle_t(vector3_t(-0.1, 0, 0), 
                                vector3_t(-0.1, 0, 0),
                                vector3_t(0.9, 0, 0));

    triangle_t t_7 = triangle_t(vector3_t(-0.1, 0, 0), 
                                vector3_t(-0.1, 0, 0),
                                vector3_t(1.1, 0, 0));
                                
    triangle_t t_8 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(1, 1, 0));

    triangle_t t_9 = triangle_t(vector3_t(0.5, 0, 0), 
                                vector3_t(0.5, 0, 0),
                                vector3_t(1, 1, 0));

    triangle_t t_10 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_11 = triangle_t(vector3_t(0, 0.5, 0), 
                                 vector3_t(0, 0.5, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_12 = triangle_t(vector3_t(0, 0.5, -0.5), 
                                 vector3_t(0, 0.5, -0.5),
                                 vector3_t(1, 1, 1));

    triangle_t t_13 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_14 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_15 = triangle_t(vector3_t(0.1, 0, 0), 
                                 vector3_t(1.1, 0, 0),
                                 vector3_t(1.1, 0, 0));

    triangle_t t_16 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(1, 0, 0));

    triangle_t t_17 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(0.9, 0, 0),
                                 vector3_t(0.9, 0, 0));

    triangle_t t_18 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(1.1, 0, 0),
                                 vector3_t(1.1, 0, 0));
                                
    triangle_t t_19 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_20 = triangle_t(vector3_t(0.5, 0, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_21 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 1));

    triangle_t t_22 = triangle_t(vector3_t(0, 0.5, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_23 = triangle_t(vector3_t(0, 0.5, -0.5), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_24 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(1, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_25 = triangle_t(vector3_t(1, 0, 0), 
                                 vector3_t(2, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_26 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(-1, 0, 0));

    triangle_t t_27 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(-1, 0, 0),
                                 vector3_t(-1, 0, 0));

    triangle_t t_28 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(0, 1, 0));

    triangle_t t_29 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0, 1, 0),
                                 vector3_t(0, 1, 0));

    triangle_t t_30 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(0, 0, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_31 = triangle_t(vector3_t(0, 0, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));
                                
    triangle_t t_32 = triangle_t(vector3_t(1.1, 0, 0), 
                                 vector3_t(1.1, 0, 0),
                                 vector3_t(2, 0, 0));

    triangle_t t_33 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-0.1, 0, 0),
                                 vector3_t(-1, 0, 0));

    triangle_t t_34 = triangle_t(vector3_t(0, 1, 0), 
                                 vector3_t(0, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_35 = triangle_t(vector3_t(0, 0.1, 0.1), 
                                 vector3_t(0, 0.1, 0.1),
                                 vector3_t(1, 1, 1));

    triangle_t t_36 = triangle_t(vector3_t(0, -1, 1), 
                                 vector3_t(0, -1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_37 = triangle_t(vector3_t(-0.1, 0, 0), 
                                 vector3_t(-1, 0, 0),
                                 vector3_t(-1, 0, 0));

    triangle_t t_38 = triangle_t(vector3_t(0, 1, 0), 
                                 vector3_t(1, 1, 0),
                                 vector3_t(1, 1, 0));

    triangle_t t_39 = triangle_t(vector3_t(0, 0.1, 0.1), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));

    triangle_t t_40 = triangle_t(vector3_t(0, -1, 1), 
                                 vector3_t(1, 1, 1),
                                 vector3_t(1, 1, 1));


    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_TRUE(t1.is_intersecting(t_3));
    EXPECT_TRUE(t1.is_intersecting(t_4));
    EXPECT_TRUE(t1.is_intersecting(t_5));
    EXPECT_TRUE(t1.is_intersecting(t_6));
    EXPECT_TRUE(t1.is_intersecting(t_7));
    EXPECT_TRUE(t1.is_intersecting(t_9));
    EXPECT_TRUE(t1.is_intersecting(t_10));
    EXPECT_FALSE(t1.is_intersecting(t_11));
    EXPECT_FALSE(t1.is_intersecting(t_12));
    EXPECT_TRUE(t1.is_intersecting(t_13));
    EXPECT_TRUE(t1.is_intersecting(t_14));
    EXPECT_TRUE(t1.is_intersecting(t_15));
    EXPECT_TRUE(t1.is_intersecting(t_16));
    EXPECT_TRUE(t1.is_intersecting(t_17));
    EXPECT_TRUE(t1.is_intersecting(t_18));
    EXPECT_TRUE(t1.is_intersecting(t_19));
    EXPECT_TRUE(t1.is_intersecting(t_20));
    EXPECT_TRUE(t1.is_intersecting(t_21));
    EXPECT_FALSE(t1.is_intersecting(t_22));
    EXPECT_FALSE(t1.is_intersecting(t_23));
    EXPECT_TRUE(t1.is_intersecting(t_24));
    EXPECT_TRUE(t1.is_intersecting(t_25));
    EXPECT_TRUE(t1.is_intersecting(t_26));
    EXPECT_TRUE(t1.is_intersecting(t_27));
    EXPECT_TRUE(t1.is_intersecting(t_28));
    EXPECT_TRUE(t1.is_intersecting(t_29));
    EXPECT_TRUE(t1.is_intersecting(t_30));
    EXPECT_TRUE(t1.is_intersecting(t_31));
    EXPECT_FALSE(t1.is_intersecting(t_32));
    EXPECT_FALSE(t1.is_intersecting(t_33));
    EXPECT_FALSE(t1.is_intersecting(t_34));
    EXPECT_FALSE(t1.is_intersecting(t_35));
    EXPECT_FALSE(t1.is_intersecting(t_36));
    EXPECT_FALSE(t1.is_intersecting(t_37));
    EXPECT_FALSE(t1.is_intersecting(t_38));
    EXPECT_FALSE(t1.is_intersecting(t_39));
    EXPECT_FALSE(t1.is_intersecting(t_40));
}

TEST(TriangleIntersect, BothTriangleDegenerateToPoints) {
    triangle_t t1 = triangle_t(vector3_t(0, 0, 0), 
                               vector3_t(0, 0, 0),
                               vector3_t(0, 0, 0));

    triangle_t t_2 = triangle_t(vector3_t(0, 0, 0), 
                                vector3_t(0, 0, 0),
                                vector3_t(0, 0, 0));


    triangle_t t_3 = triangle_t(vector3_t(0.1, 0.1, 0.1), 
                                vector3_t(0.1, 0.1, 0.1),
                                vector3_t(0.1, 0.1, 0.1));
                                

    EXPECT_TRUE(t1.is_intersecting(t_2));
    EXPECT_FALSE(t1.is_intersecting(t_3));
}
