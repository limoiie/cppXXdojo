#include <iostream>
#include <optional>

#include <gtest/gtest.h>

TEST(TestOptional, test_optional) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto num = std::make_optional(10);
    std::cout << "has value? " << num.has_value() << std::endl;
    std::cout << "value: " << num.value() << std::endl;

    std::cout << "reset optional" << std::endl;
    num.reset();

    std::cout << "num == std::nullopt? " << (num == std::nullopt) << std::endl;

    std::cout << "has value? " << num.has_value() << std::endl;
    std::cout << "value_or: " << num.value_or(100) << std::endl;

    try {
        // get value forcefully even if no value available
        std::cout << "value: " << num.value() << std::endl;
    } catch (std::bad_optional_access const& e) {
        std::cout << "error: " << e.what() << std::endl;
    }

}