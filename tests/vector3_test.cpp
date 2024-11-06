#include <gtest/gtest.h>
#include <cmath>

#include "vector3.h"
#include "common.h"

using namespace geometry;

class Vector3Test : public testing::Test {
protected:
    vector3_t zeroes_;
    vector3_t ones_ = vector3_t(1, 1, 1);
    vector3_t x_ = vector3_t(1, 0, 0);
    vector3_t y_ = vector3_t(0, 1, 0);
    vector3_t z_ = vector3_t(0, 0, 1);
    vector3_t v1_ = vector3_t(1, 2, 3);
    vector3_t v2_ = vector3_t(-3, 5, 4);
    vector3_t v3_ = vector3_t(6.5, -7.1, 0.1);
    vector3_t v4_ = vector3_t(1.1, 3.7, 9.5);
};

TEST_F(Vector3Test, Equality) {
    EXPECT_EQ(v1_, v1_);
    EXPECT_NE(v1_, v2_);

    EXPECT_EQ(v3_, v3_);
    EXPECT_NE(v3_, v4_);

    EXPECT_NE(zeroes_, ones_);
}

TEST_F(Vector3Test, Addition) {
    EXPECT_EQ(v1_ + v2_, vector3_t(-2, 7, 7));
    EXPECT_EQ(v1_ + v1_, vector3_t(2, 4, 6));
    EXPECT_EQ(v3_ + v4_, vector3_t(7.6, -3.4, 9.6));

    EXPECT_EQ(v1_ + zeroes_, v1_);
    EXPECT_EQ(v3_ + zeroes_, v3_);

    EXPECT_EQ(x_ + y_ + z_, ones_);
}

TEST_F(Vector3Test, Module) {
    EXPECT_TRUE(eq_double(ones_.mod(), sqrt(3)));
    EXPECT_TRUE(eq_double(zeroes_.mod(), 0));
    EXPECT_TRUE(eq_double(x_.mod(), 1));

    EXPECT_TRUE(eq_double(v1_.mod(), sqrt(14)));
    EXPECT_TRUE(eq_double(v3_.mod(),
                                sqrt(6.5 * 6.5 + 7.1 * 7.1 + 0.1 * 0.1)));
}

TEST_F(Vector3Test, Dot) {
    EXPECT_TRUE(eq_double(x_.dot(y_), 0));
    EXPECT_TRUE(eq_double(zeroes_.dot(v1_), 0));
    EXPECT_TRUE(eq_double(v2_.dot(v4_), v4_.dot(v2_)));

    EXPECT_TRUE(eq_double(v3_.dot(x_), 6.5));
    EXPECT_TRUE(eq_double(v1_.dot(v2_), 19));

    EXPECT_TRUE(eq_double(sqrt(v1_.dot(v1_)), v1_.mod()));
    EXPECT_TRUE(eq_double(sqrt(v3_.dot(v3_)), v3_.mod()));
}

TEST_F(Vector3Test, Cross) {
    EXPECT_EQ(v3_.cross(v3_), zeroes_);
    EXPECT_EQ(v1_.cross(zeroes_), zeroes_);
    EXPECT_EQ(x_.cross(y_), z_);

    EXPECT_EQ(v2_.cross(v4_), -v4_.cross(v2_));

    EXPECT_EQ(v1_.cross(v2_), vector3_t(-7, -13, 11));
}

TEST_F(Vector3Test, Normalize) {
    vector3_t old_x_ = x_;
    x_.normalize();
    EXPECT_EQ(old_x_, x_);

    v1_.normalize();
    EXPECT_TRUE(eq_double(v1_.mod(), 1));

    v3_.normalize();
    EXPECT_TRUE(eq_double(v3_.mod(), 1));

    zeroes_.normalize();
    EXPECT_TRUE(eq_double(zeroes_.mod(), 0));
}
