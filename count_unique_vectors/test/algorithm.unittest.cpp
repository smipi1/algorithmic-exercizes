#include <vector>
#include <gtest/gtest.h>

#include "algorithm.h"

using namespace std;

class test_Api: public testing::Test {
protected:
    test_Api()
    {
    }

    virtual ~test_Api()
    {
    }

    virtual void SetUp()
    {
    }

    virtual void TearDown()
    {
    }
};

TEST_F(test_Api, unalighned_points_are_counted_separately)
{
    vector<Point> points = {
        { 1, 1 },
        { 1, 2 }
    };
    EXPECT_EQ(count_unique_vectors(points), 2);
}

TEST_F(test_Api, aligned_points_quadrant_1_count_as_one)
{
    vector<Point> points = {
        { 2, 3 },
        { 4, 6 }
    };
    EXPECT_EQ(count_unique_vectors(points), 1);
}

TEST_F(test_Api, aligned_points_quadrant_2_count_as_one)
{
    vector<Point> points = {
        { -2, 3 },
        { -4, 6 }
    };
    EXPECT_EQ(count_unique_vectors(points), 1);
}

TEST_F(test_Api, aligned_points_quadrant_3_count_as_one)
{
    vector<Point> points = {
        { -2, -3 },
        { -4, -6 }
    };
    EXPECT_EQ(count_unique_vectors(points), 1);
}

TEST_F(test_Api, aligned_points_quadrant_4_count_as_one)
{
    vector<Point> points = {
        { 2, -3 },
        { 4, -6 }
    };
    EXPECT_EQ(count_unique_vectors(points), 1);
}

TEST_F(test_Api, points_on_opposite_sides_are_counted_separately)
{
    vector<Point> points = {
        { 2, 2 },
        { -2, -2 }
    };
    EXPECT_EQ(count_unique_vectors(points), 2);
}

TEST_F(test_Api, points_on_opposite_sides_op_x_axis_are_counted_separately)
{
    vector<Point> points = {
        { 2, 0 },
        { -2, 0 }
    };
    EXPECT_EQ(count_unique_vectors(points), 2);
}

TEST_F(test_Api, points_on_opposite_sides_op_y_axis_are_counted_separately)
{
    vector<Point> points = {
        { 0, 2 },
        { 0, -2 }
    };
    EXPECT_EQ(count_unique_vectors(points), 2);
}
