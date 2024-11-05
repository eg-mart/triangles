#include <gtest/gtest.h>

#include "segment.h"
#include "vector3.h"
#include "common.h"

using namespace geometry;

TEST(SegmentTest, SimpleIntersection) {
    segment_t segment1 = segment_t(vector3_t(-1, 0, 1), vector3_t(1, 0, 1));
    segment_t segment2 = segment_t(vector3_t(0, -1, 1), vector3_t(0, 1, 1));
    segment_t segment3 = segment_t(vector3_t(-1, 0, 1), vector3_t(1, 1, 1));
    segment_t segment4 = segment_t(vector3_t(-1, -1, 1), vector3_t(-1, 1, 1));

    segment_t::intersection_t intersection_center = segment1.intersect(segment2);
    segment_t::intersection_t intersection_point_point = segment1.intersect(segment3);
    segment_t::intersection_t intersection_point_center = segment1.intersect(segment4);

    EXPECT_EQ(intersection_center.index(), 1);
    EXPECT_EQ(intersection_point_point.index(), 1);
    EXPECT_EQ(intersection_point_center.index(), 1);
    EXPECT_EQ(std::get<vector3_t>(intersection_center), vector3_t(0, 0, 1));
    EXPECT_EQ(std::get<vector3_t>(intersection_point_point), vector3_t(-1, 0, 1));
    EXPECT_EQ(std::get<vector3_t>(intersection_point_center), vector3_t(-1, 0, 1));
}

TEST(SegmentTest, SegmentCoincedence) {
    segment_t segment1 = segment_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0));
    segment_t segment2 = segment_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0));
    segment_t segment3 = segment_t(vector3_t(0.5, 0, 0), vector3_t(1.5, 0, 0));
    segment_t segment_ans = segment_t(vector3_t(0.5, 0, 0), vector3_t(1, 0, 0));

    segment_t::intersection_t intersection_full = segment1.intersect(segment2);
    segment_t::intersection_t intersection_part = segment1.intersect(segment3);

    EXPECT_EQ(intersection_full.index(), 2);
    EXPECT_EQ(intersection_part.index(), 2);
    EXPECT_EQ(std::get<segment_t>(intersection_full), segment1);
    EXPECT_EQ(std::get<segment_t>(intersection_part), segment_ans);
}

TEST(SegmentTest, SkewLines) {
    segment_t segment1 = segment_t(vector3_t(0, 0, 0), vector3_t(1, 1, 0));
    segment_t segment2 = segment_t(vector3_t(1, 0, 1), vector3_t(0, 1, 1));

    segment_t::intersection_t intersection = segment1.intersect(segment2);

    EXPECT_TRUE(std::holds_alternative<std::monostate>(intersection));
}

TEST(SegmentTest, Parallel) {
    segment_t segment1 = segment_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0));
    segment_t segment2 = segment_t(vector3_t(0, 1, 0), vector3_t(1, 1, 0));

    segment_t::intersection_t intersection = segment1.intersect(segment2);

    EXPECT_TRUE(std::holds_alternative<std::monostate>(intersection));
}

TEST(SegmentTest, NotNormal) {
    segment_t segment1 = segment_t(vector3_t(0, 0, 0), vector3_t(2, 1, 0));
    segment_t segment2 = segment_t(vector3_t(0, 1, 0), vector3_t(2, 0, 0));
    segment_t segment3 = segment_t(vector3_t(0, 1, 1), vector3_t(2, 0, -1));

    segment_t::intersection_t intersection_on_plane = segment1.intersect(segment2);
    segment_t::intersection_t intersection_in_space = segment1.intersect(segment3);

    EXPECT_EQ(intersection_on_plane.index(), 1);
    EXPECT_EQ(intersection_in_space.index(), 1);
    EXPECT_EQ(std::get<vector3_t>(intersection_on_plane), vector3_t(1, 0.5, 0));
    EXPECT_EQ(std::get<vector3_t>(intersection_in_space), vector3_t(1, 0.5, 0));
}