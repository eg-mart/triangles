#include <gtest/gtest.h>

#include "plane.h"
#include "vector3.h"
#include "common.h"

using namespace geometry;

TEST(PlaneTest, FromThreePoints) {
    plane_t plane = plane_t(vector3_t(0, 0, 0), vector3_t(1, 0, 0),
                            vector3_t(0, 1, 0));
    EXPECT_EQ(plane.normal, vector3_t(0, 0, 1));
    EXPECT_EQ(plane.origin, vector3_t(0, 0, 0));

    plane = plane_t(vector3_t(1, 0, 0), vector3_t(0, 1, 0),
                    vector3_t(0, 0, 1));
    vector3_t norm = vector3_t(1, 1, 1);
    norm.normalize();
    vector3_t orig = vector3_t(1. / 3, 1. / 3, 1. / 3);
    EXPECT_EQ(plane.normal, norm);
    EXPECT_EQ(plane.origin, orig);
}
