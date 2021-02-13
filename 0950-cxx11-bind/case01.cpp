#include <iostream>

#include <gtest/gtest.h>

/**
 * The function template bind generates a forwarding call wrapper for f.
 * Calling this wrapper is equivalent to invoking f with some of its arguments
 * bound to args.
 *
 * reference from https://en.cppreference.com/w/cpp/utility/functional/bind
 */


static
void f(int arg1, int arg2, int arg3, const int& arg4, int arg5) {
    std::cout << "Call f with "
              << arg1 << ' ' << arg2 << ' ' << arg3 << ' '
              << arg4 << ' ' << arg5 << std::endl;
}

static
long g(int arg1) {
    std::cout << "Call g with " << arg1 << std::endl;
    return arg1 + 1000;
}

TEST(TestBind, test_bind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto fn_add_one_to_five = std::bind(f, 1, 2, 3, 4, 5); // NOLINT(modernize-avoid-bind)
    fn_add_one_to_five();
}

/**
 * Bind partially with std::placeholders
 */
TEST(TestBind, test_partially_bind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;  // for _1, _2, _3, ...
    auto fn_times_five = std::bind(f, _1, _1, _1, _1, _1); // NOLINT(modernize-avoid-bind)
    fn_times_five(3);  // the five `_1` will be replaced by 3

    auto bind_f = std::bind(f, _2, _2, _1, _1, 3); // NOLINT(modernize-avoid-bind)
    bind_f(37, 73);  // the two `_1`(/`_2`) will be replaced by 37(/73)
}

/**
 * Nested bind with sharing the std::placeholders
 */
TEST(TestBind, test_nested_bind) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;  // for _1, _2, _3, ...
    auto bind_func = std::bind(f, _1, std::bind(g, _2), _3, 4, 5); // NOLINT(modernize-avoid-bind)
    bind_func(1, 2, 3);
}

struct Foo {
    int data = 10;
    void print_sum(int arg1) const {
        std::cout << "Foo::sum of " << arg1 << ',' << data << " = " << arg1 + data << std::endl;
    }
};

/**
 * Bind with class member
 */
TEST(TestBind, test_bind_class_member) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " <<  __PRETTY_FUNCTION__ << " ..." << std::endl;

    using namespace std::placeholders;  // for _1, _2, _3, ...
    auto foo_obj = Foo();

    // bind with member function
    auto fn_add_five_to_foo = std::bind(&Foo::print_sum, _1, 5); // NOLINT(modernize-avoid-bind)
    fn_add_five_to_foo(foo_obj);

    // bind with member data
    auto fn_get_data_of_foo = std::bind(&Foo::data, _1); // NOLINT(modernize-avoid-bind)
    std::cout << "Foo::data = " << fn_get_data_of_foo(foo_obj) << std::endl;
}