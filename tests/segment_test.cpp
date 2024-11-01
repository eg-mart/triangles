#include <gtest/gtest.h>

#include "segment.h"
#include "vector3.h"
#include "common.h"

using namespace geometry;

TEST(SegmentTest, SimpleIntersection) {
    segment_t segment1 = segment_t(vector3_t(-1, 0, 1), vector3_t(1, 0, 1));
    segment_t segment2 = segment_t(vector3_t(0, -1, 1), vector3_t(0, 1, 1));
    segment_t::intersection_t intersection = segment1.intersect(segment2);

    EXPECT_EQ(intersection.index(), 1);
    EXPECT_EQ(std::get<vector3_t>(intersection), vector3_t(0, 0, 1));
}
