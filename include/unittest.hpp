#pragma once

#include <format>
#include <iostream>
#include <memory>
#include <source_location>
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

inline std::vector<std::pair<std::unique_ptr<test>, std::string>> g_tests;

inline int run_tests()
{
    int rc = 0;

    for (const auto& [t, name] : g_tests) {
        try {
            std::cout << "Running test [" << name << "]" << std::endl;
            t->setup();
            t->run();
            t->teardown();
            std::cout << "Finished test [" << name << "]" << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Test [" << name << "] failed: " << e.what() << std::endl;

            rc = 1;
        }
    }

    return rc;
}

inline void add_test(std::unique_ptr<test> t, std::string name)
{
    g_tests.emplace_back(std::move(t), name);
}

} // namespace ut

#define ASSERT_TRUE(cond)                                                                                              \
    do {                                                                                                               \
        if (!(cond)) {                                                                                                 \
            constexpr std::source_location location = std::source_location::current();                                 \
            throw std::runtime_error(                                                                                  \
                std::format("Assertion at {}:{} failed: " #cond, location.file_name(), location.line()));              \
        }                                                                                                              \
    } while (0)

#define ASSERT_FALSE(cond)                                                                                             \
    do {                                                                                                               \
        if ((cond)) {                                                                                                  \
            constexpr std::source_location location = std::source_location::current();                                 \
            throw std::runtime_error(                                                                                  \
                std::format("Assertion at {}:{} failed: " #cond, location.file_name(), location.line()));              \
        }                                                                                                              \
    } while (0)

#define ASSERT_EQ(val1, val2)                                                                                          \
    do {                                                                                                               \
        if ((val1) != (val2)) {                                                                                        \
            constexpr std::source_location location = std::source_location::current();                                 \
            throw std::runtime_error(                                                                                  \
                std::format(                                                                                           \
                    "Assertion at {}:{} failed: " #val1 " == " #val2 " ({} != {})",                                    \
                    location.file_name(),                                                                              \
                    location.line(),                                                                                   \
                    (val1),                                                                                            \
                    (val2)));                                                                                          \
        }                                                                                                              \
    } while (0)

#define ASSERT_NEQ(val1, val2)                                                                                         \
    do {                                                                                                               \
        if ((val1) == (val2)) {                                                                                        \
            constexpr std::source_location location = std::source_location::current();                                 \
            throw std::runtime_error(                                                                                  \
                std::format(                                                                                           \
                    "Assertion at {}:{} failed: " #val1 " != " #val2 " ({} == {})",                                    \
                    location.file_name(),                                                                              \
                    location.line(),                                                                                   \
                    (val1),                                                                                            \
                    (val2)));                                                                                          \
        }                                                                                                              \
    } while (0)

#define ENV_TEST(test, name)                                                                                           \
    class test_##test##_##name : public test {                                                                         \
    public:                                                                                                            \
        void run() override;                                                                                           \
    };                                                                                                                 \
    static struct test_##test##_##name##_registrar {                                                                   \
        test_##test##_##name##_registrar()                                                                             \
        {                                                                                                              \
            ut::add_test(std::make_unique<test_##test##_##name>(), std::string(#test "_" #name));                      \
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
            ut::add_test(std::make_unique<test_##name>(), std::string(#name));                                         \
        }                                                                                                              \
    } test_##name##_registrar_handle;                                                                                  \
    void test_##name::run()

#define TEST_MAIN()                                                                                                    \
    int main()                                                                                                         \
    {                                                                                                                  \
        return ut::run_tests();                                                                                        \
    }
