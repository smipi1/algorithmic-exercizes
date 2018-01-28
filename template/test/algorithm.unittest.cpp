#include <gtest/gtest.h>

#include "algorithm.h"

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

TEST_F(test_Api, algorithm_returns_0)
{
    ASSERT_EQ(algorithm(), 0);
}
