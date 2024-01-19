#include <iostream>
#include <variant>

#include <gtest/gtest.h>

/**
 * The class template std::variant represents a type-safe union. An instance
 * of std::variant at any given time either holds a value of one of its
 * alternative types, or in the case of error - no value (this state is hard
 * to achieve, see valueless_by_exception).
 *
 * reference from https://en.cppreference.com/w/cpp/utility/variant
 */

TEST(TestVariant, test_variant_get) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::variant<int, float> v;

    v = 12;
    ASSERT_EQ(v.index(), 0);          // int indexes 0 in <int, float>
    ASSERT_EQ(std::get<int>(v), 12);  // get int from variant since it has a int now
    ASSERT_EQ(std::get<0>(v), 12);    // same as previous line

    v = 12.5f;
    ASSERT_EQ(v.index(), 1);               // float indexes 1 <int, float>
    ASSERT_EQ(std::get<float>(v), 12.5f);  // get float from variant since it has a float now
    ASSERT_EQ(std::get<1>(v), 12.5f);      // same as previous line
}

TEST(TestVariant, test_bad_variant_access) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::variant<int, float> v;
    // only int and float value can be assigned to v
    v = 12;

    //v = std::string("string");  // error: No viable overloaded '=' for std::string
    //v = 12.5;                   // error: No viable overloaded '=' for double

    // bad case: get float while the variant stores an int value
    EXPECT_THROW(
            { std::get<float>(v); },
            std::bad_variant_access
    );
    EXPECT_THROW(
            { std::get<1>(v); },
            std::bad_variant_access
    );

    //std::get<2>(v);       // error: get by an out-range index which ought be in [0,2)
    //std::get<double>(v);  // error: no double in [int, float]
}

TEST(TestVariant, test_holds_alternative) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    std::variant<int, float, std::string> v;

    v = 10;
    ASSERT_TRUE(std::holds_alternative<int>(v));
    ASSERT_FALSE(std::holds_alternative<float>(v));
    //ASSERT_FALSE(std::holds_alternative<double>(v));  // this won't be compiled

    v = 10.5f;
    ASSERT_TRUE(std::holds_alternative<float>(v));

    v = "string";
    ASSERT_TRUE(std::holds_alternative<std::string>(v));
}
