#include "unittest.hpp"

static int g_var = 0;

SIMPLE_TEST(one)
{
    g_var = 42;
}

SIMPLE_TEST(two)
{
    ASSERT_EQ(g_var, 42);
}

TEST_MAIN()
