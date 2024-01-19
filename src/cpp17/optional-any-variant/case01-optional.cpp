#include <iostream>
#include <optional>

#include <gtest/gtest.h>

TEST(TestOptional, test_optional) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto num = std::make_optional(10);

    // num has value
    std::cout << "has value? " << num.has_value() << std::endl;
    std::cout << "value: " << num.value() << std::endl;
    ASSERT_TRUE(num.has_value());
    ASSERT_EQ(num.value(), 10);

    // reset num will make it empty
    std::cout << "reset std::optional" << std::endl;
    num.reset();

    // empty optional will be equal to std::nullopt
    std::cout << "num == std::nullopt? " << (num == std::nullopt) << std::endl;
    ASSERT_EQ(num, std::nullopt);

    // now num has no value
    std::cout << "has value? " << num.has_value() << std::endl;
    std::cout << "value_or: " << num.value_or(100) << std::endl;
    ASSERT_FALSE(num.has_value());

    // get from empty optional forcefully will throw std::bad_optional_access
    EXPECT_THROW(
            { num.value(); },
            std::bad_optional_access
    );

}