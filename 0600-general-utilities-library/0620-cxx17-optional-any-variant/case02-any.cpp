#include <iostream>
#include <any>

#include <gtest/gtest.h>

/**
 * The class any describes a type-safe container for single values of any type.
 *
 * reference from https://en.cppreference.com/w/cpp/utility/any
 */

TEST(TestAny, test_any_any_cast) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::cout << std::boolalpha;

    // any type and any_cast
    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
    a = 3.14;
    std::cout << a.type().name() << ": " << std::any_cast<double>(a) << '\n';
    a = true;
    std::cout << a.type().name() << ": " << std::any_cast<bool>(a) << '\n';
}

TEST(TestAny, test_bad_cast) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::any a = 1;
    try {
        std::cout << std::any_cast<float>(a) << std::endl;
    } catch (std::bad_any_cast const& e) {
        std::cout << "exception when any_cast from int to float: " << e.what() << std::endl;
    }

    a.reset();
    try {
        std::cout << std::any_cast<int>(a) << std::endl;
    } catch (std::bad_any_cast const& e) {
        std::cout << "exception when any_cast on no value: " << e.what() << std::endl;
    }
}

TEST(TestAny, test_has_value_reset) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::any a = 1;
    std::cout << "has value? " << a.has_value() << std::endl;

    std::cout << "reset any" << std::endl;
    a.reset();
    std::cout << "has value? " << a.has_value() << std::endl;
}

TEST(TestAny, test_pointer_to_contained_data) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::any a = 1;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';

    int* p_a = std::any_cast<int>(&a);
    std::cout << "*p_a: " << *p_a << std::endl;

    *p_a = 2;
    std::cout << a.type().name() << ": " << std::any_cast<int>(a) << '\n';
}