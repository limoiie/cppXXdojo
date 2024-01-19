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

    int arr[2] = {2, 3};

    // When binding an array to variables,
    // it will be copied to a temporary array firstly.
    // The value of the original is then copied into that temporary array,
    // which the identifiers will be bound to.
    auto [x, y] = arr;

    // When binding an array to reference, no copy occurs.
    // Instead, the identifiers will refer to the original array directly.
    auto &[a, b] = arr;

    ASSERT_EQ(x, arr[0]);
    ASSERT_EQ(y, arr[1]);
    ASSERT_EQ(a, arr[0]);
    ASSERT_EQ(b, arr[1]);

    arr[0] = 4;

    // The identifiers are bound to the temporary array,
    // not the original array.
    ASSERT_NE(x, arr[0]);
    ASSERT_EQ(y, arr[1]);

    // The identifiers are bound to the original array,
    // not the temporary array.
    ASSERT_EQ(a, arr[0]);
    ASSERT_EQ(b, arr[1]);
}

TEST(TestStructuredBinding, test_bind_a_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    float x{};
    std::string y{};
    int z{};

    std::tuple<float &, std::string &&, int> tpl(x, std::move(y), z);
    const auto &[a, b, c] = tpl;

    // decltype(a) is `float&`
    ASSERT_TRUE((std::is_same_v<decltype(a), float &>));

    // decltype(b) is `std::string&&`
    ASSERT_TRUE((std::is_same_v<decltype(b), std::string &&>));

    // decltype(c) is `const int`
    ASSERT_TRUE((std::is_same_v<decltype(c), const int>));
}

TEST(TestStructuredBinding, test_bind_on_tie_and_make_tuple) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    int a{};

#pragma clang diagnostic push
#pragma ide diagnostic ignored "UnusedLocalVariable"

    // NOTE:
    // The declaration preceding `[' applies to the temporary object,
    // not the identifiers wrapped in `[' and `]'.

    /// What is `std::tie`?
    ///
    /// `std::tie` is a function template
    /// that returns a tuple of lvalue references to its arguments.
    /// The tied references are not references to the arguments passed to `std::tie`,
    /// but to the original objects that were passed to the function.
    /// The tied references are obtained by calling `std::forward` on the arguments.
    /// The tuple returned by std::tie is a temporary object.
    /// The lifetime of the temporary object
    /// is the same as the lifetime of the reference returned by `std::tie`.

    const auto &[u] = std::tie(a);
    ASSERT_TRUE((std::is_same_v<decltype(u), int &>));

    auto [v] = std::tie(a);
    ASSERT_TRUE((std::is_same_v<decltype(v), int &>));

    // error:
    // cannot bind a non-const lvalue reference (the identifier)
    // to a rvalue (the temporary object)
    //auto&     [w] = std::tie(a);

    auto &&[t] = std::tie(a);
    ASSERT_TRUE((std::is_same_v<decltype(t), int &>));

    /// What is `std::make_tuple`?
    ///
    /// `std::make_tuple` is a function template
    /// that returns a tuple of values,
    /// where the types of the values are the types of the arguments.
    /// The tuple returned by `std::make_tuple` is a temporary object.
    /// The lifetime of the temporary object
    /// is the same as the lifetime of the reference returned by `std::make_tuple`.

    const auto &[x] = std::make_tuple(a);
    ASSERT_TRUE((std::is_same_v<decltype(x), const int>));

    auto [y] = std::make_tuple(a);
    ASSERT_TRUE((std::is_same_v<decltype(y), int>));

    // error:
    // cannot bind a non-const lvalue reference (the identifier)
    // to a rvalue (the temporary object)
    //auto&     [_] = std::make_tuple(a);

    auto &&[z] = std::make_tuple(a);
    ASSERT_TRUE((std::is_same_v<decltype(z), int>));

#pragma clang diagnostic pop
}

struct S {
    mutable int x;
    volatile double y;
};

TEST(TestStructuredBinding, test_bind_data_members) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto f = S();
    const auto [x, y] = f;

    // `decltype(x)` is not const since `S::x` is declared as mutable
    ASSERT_TRUE((std::is_same_v<decltype(x), decltype(S::x)>));

    // `decltype(y)` is const since `S::x` is declared as mutable
    ASSERT_TRUE((std::is_same_v<decltype(y), const decltype(S::y)>));
}