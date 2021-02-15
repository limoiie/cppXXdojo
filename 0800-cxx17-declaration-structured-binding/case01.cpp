#include <iostream>
#include <string>
#include <tuple>

#include <gtest/gtest.h>

/**
 * Binds the specified names to subobjects or elements of the initializer.
 *
 * Like a reference, a structured binding is an alias to an existing object.
 * Unlike a reference, a structured binding does not have to be of a
 * reference type.
 *
 * reference from https://en.cppreference.com/w/cpp/language/structured_binding
 */

TEST(TestStructuredBinding, test_bind_an_array) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    int a[2] = {2, 3};

    auto [x, y] = a;    // creates e[2], copies a into e, then x refers to e[0], y refers to e[1]
    auto& [rx, ry] = a; // rx refers to a[0], ry refers to a[1]

    ASSERT_EQ(x, 2); ASSERT_EQ(rx, 2);
    ASSERT_EQ(y, 3); ASSERT_EQ(ry, 3);

    rx = 4;
    ASSERT_EQ(a[0], 4);
    ASSERT_EQ(a[1], 3);

    y = 5;
    ASSERT_EQ(a[0], 4);
    ASSERT_EQ(a[1], 3);
}

TEST(TestStructuredBinding, test_bind_a_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    float        x{};
    std::string  y{};
    int          z{};

    std::tuple<float&, std::string&&, int> tpl(x, std::move(y), z);
    const auto& [a, b, c] = tpl;

    // a names a structured binding that refers to x; decltype(a) is float&
    ASSERT_TRUE((std::is_same_v<decltype(a), float&>));
    // b names a structured binding that refers to y; decltype(b) is std::string&&
    ASSERT_TRUE((std::is_same_v<decltype(b), std::string&&>));
    // c names a structured binding that refers to the 3rd element of tpl; decltype(c) is const int
    ASSERT_TRUE((std::is_same_v<decltype(c), const int>));
}

TEST(TestStructuredBinding, test_bind_on_tie_and_make_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;
    int a = 1;

    // NOTE: The portion of the declaration preceding [ applies to the hidden variable e,
    // not to the introduced identifiers. Remember the hidden variable e is a rvalue.
    const auto& [u] = std::tie(a);          ASSERT_TRUE((std::is_same_v<decltype(u), int&>));
    auto        [v] = std::tie(a);          ASSERT_TRUE((std::is_same_v<decltype(v), int&>));
    //auto&     [w] = std::tie(a);          // error: cannot bind non-const lvalue reference to an rvalue
    auto&&      [t] = std::tie(a);          ASSERT_TRUE((std::is_same_v<decltype(t), int&>));

    const auto& [x] = std::make_tuple(a);   ASSERT_TRUE((std::is_same_v<decltype(x), const int>));
    auto        [y] = std::make_tuple(a);   ASSERT_TRUE((std::is_same_v<decltype(y), int>));
    //auto&     [_] = std::make_tuple(a);  // error: cannot bind non-const lvalue reference to an rvalue
    auto&&      [z] = std::make_tuple(a);   ASSERT_TRUE((std::is_same_v<decltype(z), int>));
}

struct S {
    mutable int x;
    volatile double y;
};

TEST(TestStructuredBinding, test_bind_data_members) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto f = S();
    const auto [x, y] = f;

    ASSERT_TRUE((std::is_same_v<decltype(x), decltype(S::x)>));        // decltype(x) is not const cause mutable
    ASSERT_TRUE((std::is_same_v<decltype(y), const decltype(S::y)>));  // decltype(y) is const
}