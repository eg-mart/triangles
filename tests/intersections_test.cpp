#include <gtest/gtest.h>
#include <variant>

#include "vector3.h"
#include "plane.h"
#include "segment.h"
#include "intersections.h"

using namespace geometry;

TEST(IntersectionsTest, Simple) {
    segment_t seg = segment_t(vector3_t(-1, 0, 1), vector3_t(1, 0, 1));
    plane_t plane = plane_t(vector3_t(1, 0, 0), vector3_t(0, 0, 1));
    auto intersection = segment_plane_intersect(seg, plane);

    EXPECT_TRUE(std::holds_alternative<vector3_t>(intersection));
    EXPECT_EQ(std::get<vector3_t>(intersection), vector3_t(0, 0, 1));
}

TEST(IntersectionsTest, AtZero) {
    segment_t seg = segment_t(vector3_t(2.5, 1, 3), vector3_t(-2.5, -1, -3));
    plane_t plane = plane_t(vector3_t(0.58, 0.08, -0.81), vector3_t(0, 0, 0));
    auto intersection = segment_plane_intersect(seg, plane);

    EXPECT_TRUE(std::holds_alternative<vector3_t>(intersection));
    EXPECT_EQ(std::get<vector3_t>(intersection), vector3_t(0, 0, 0));
}

TEST(IntersectionsTest, Parallel) {
    segment_t seg = segment_t(vector3_t(-1, -1, 1), vector3_t(1, 1, 1));
    plane_t plane = plane_t(vector3_t(0, 0, 1), vector3_t(0, 0, -1));
    auto intersection = segment_plane_intersect(seg, plane);

    EXPECT_TRUE(std::holds_alternative<std::monostate>(intersection));
}

TEST(IntersectionsTest, SegmentInsidePlane) {
    segment_t seg = segment_t(vector3_t(0, -1, -1), vector3_t(0, 1, 1));
    plane_t plane = plane_t(vector3_t(1, 0, 0), vector3_t(0, 0, 0));
    auto intersection = segment_plane_intersect(seg, plane);

    EXPECT_TRUE(std::holds_alternative<segment_t>(intersection));
    EXPECT_EQ(std::get<segment_t>(intersection), seg);
}

TEST(IntersectionsTest, OutOfSegment) {
    segment_t seg = segment_t(vector3_t(1.5, 2.3, 0.8), vector3_t(4.5, 3.3, 5.1));
    plane_t plane = plane_t(vector3_t(1, 0, 0), vector3_t(1, 2, -1));
    auto intersection = segment_plane_intersect(seg, plane);

    EXPECT_TRUE(std::holds_alternative<std::monostate>(intersection));
}
