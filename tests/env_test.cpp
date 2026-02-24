#include "unittest.hpp"

class env_test : public ut::test {
public:
    void setup() override
    {
        var_ = 0;
    }

    void teardown() override
    {
        var_ = 0;
    }
protected:
    int var_; 
};

ENV_TEST(env_test, one)
{
    var_ = 42;
}

ENV_TEST(env_test, two)
{
    ASSERT_EQ(var_, 0);
}

TEST_MAIN()
