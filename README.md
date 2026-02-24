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
