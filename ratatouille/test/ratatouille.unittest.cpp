#include <gtest/gtest.h>

#include "ratatouille.h"

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

TEST_F(test_Api, ratatouille_returns_0)
{
    ASSERT_EQ(ratatouille(), 0);
}
