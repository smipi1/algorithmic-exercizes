#include <gtest/gtest.h>

#include "alphabet_cake.h"

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

TEST_F(test_Api, alphabet_cake_returns_0)
{
    ASSERT_EQ(alphabet_cake(), 0);
}
