# Minimalist unit testing library

## How to use

Link library to your project:

```
target_link_libraries(your-test unittest)
```

Create test:

```C++
#include "unittest.hpp"

SIMPLE_TEST(your_test_name)
{
    ASSERT_EQ(1 + 1, 2);
}

TEST_MAIN()
```

Run test using ctest or by hand.

You also can define your own complex tesing enviroment:

```C++
#include "unittest.hpp"

class my_test_class : public ut::test {
public:
    void setup() override
    {
        var_ = 42;
    }

    void teardown() override
    {
        var_ = 0;
    }
protected:
    int var_; 
};

ENV_TEST(my_test_class, my_test)
{
    ASSERT_EQ(var_, 42);
}

TEST_MAIN()
```
