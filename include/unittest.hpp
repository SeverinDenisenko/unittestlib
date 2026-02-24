#pragma once

#include <iostream>
#include <memory>
#include <vector>

namespace ut {

class test {
public:
    virtual void setup()
    {
    }

    virtual void teardown()
    {
    }

    virtual void run() = 0;

    virtual ~test() = default;
};

inline std::vector<std::unique_ptr<test>> g_tests;

inline int run_tests()
{
    for (const std::unique_ptr<test>& t : g_tests) {
        try {
            t->setup();
            t->run();
            t->teardown();
        } catch (const std::exception& e) {
            std::cerr << "Test failed: " << e.what() << std::endl;

            return 1;
        }
    }

    return 0;
}

inline void add_test(std::unique_ptr<test> t)
{
    g_tests.push_back(std::move(t));
}

} // namespace ut

#define ASSERT_TRUE(cond)                                                                                              \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            throw std::runtime_error("Assertion failed: " #cond);                                                      \
        }                                                                                                              \
    } while (0)

#define ASSERT_EQ(val1, val2) ASSERT_TRUE((val1) == (val2))

#define ASSERT_NEQ(val1, val2) ASSERT_TRUE((val1) != (val2))

#define ENV_TEST(test, name)                                                                                           \
    class test_##test##_##name : public test {                                                                         \
    public:                                                                                                            \
        void run() override;                                                                                           \
    };                                                                                                                 \
    static struct test_##test##_##name##_registrar {                                                                   \
        test_##test##_##name##_registrar()                                                                             \
        {                                                                                                              \
            ut::add_test(std::make_unique<test_##test##_##name>());                                                    \
        }                                                                                                              \
    } test_##test##_##name##_registrar_handle;                                                                         \
    void test_##test##_##name::run()

#define SIMPLE_TEST(name)                                                                                              \
    class test_##name : public ut::test {                                                                              \
    public:                                                                                                            \
        void run() override;                                                                                           \
    };                                                                                                                 \
    static struct test_##name##_registrar {                                                                            \
        test_##name##_registrar()                                                                                      \
        {                                                                                                              \
            ut::add_test(std::make_unique<test_##name>());                                                             \
        }                                                                                                              \
    } test_##name##_registrar_handle;                                                                                  \
    void test_##name::run()

#define TEST_MAIN()                                                                                                    \
    int main()                                                                                                         \
    {                                                                                                                  \
        return ut::run_tests();                                                                                        \
    }
