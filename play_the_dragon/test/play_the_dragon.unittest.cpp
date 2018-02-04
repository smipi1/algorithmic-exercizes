#include <gtest/gtest.h>

#include "play_the_dragon.h"

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

TEST_F(test_Api, play_the_dragon_returns_0)
{
    ASSERT_EQ(play_the_dragon(), 0);
}
