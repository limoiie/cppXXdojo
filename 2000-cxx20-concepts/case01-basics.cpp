#include <iostream>
#include <concepts>
#include <vector>
#include <thread>

#include <gtest/gtest.h>

/**
 * Class templates, function templates, and non-template functions (typically members
 * of class templates) may be associated with a constraint, which specifies the
 * requirements on template arguments, which can be used to select the most appropriate
 * function overloads and template specializations.
 *
 * Constraints may also be used to limit automatic type deduction in variable
 * declarations and function return types to only the types that satisfy specified
 * requirements.
 *
 * Named sets of such requirements are called concepts. Each concept is a predicate,
 * evaluated at compile time, and becomes a part of the interface of a template where
 * it is used as a constraint:
 *
 * reference from https://en.cppreference.com/w/cpp/experimental/constraints
 */

using namespace std::literals;

template<bool V>
struct assert_true {
};

template<>
struct assert_true<true> {
    constexpr static bool value = true;
};

/**
 * Define a concept which requires `T` is comparable by `==` and `!=` and the
 * result type of comparison should be bool
 */
template<typename T>
concept EqualityComparable = requires(T a, T b) {
    // here can be more than one requirement separated by `;`.
    //   Each requirement is satisfied if it's a valid expression (no need be ture)
    assert_true<std::same_as<decltype(a == b), bool>>::value;
    // next line is a much more concise form of the above line, where the type of
    //   expression clause `{ a != b}` will be append to the argument list of
    //   std::same_as (behind bool in this case) automatically.
    //   This line is valid if and only if `std::same_as<bool>` evaluates to true
    //   after appending the type of expression clause `{ a != b }`
    { a != b } -> std::same_as<bool>;
};

/**
 * Require/Use a concept to constraint `T` be comparable by `==` and `!=` which
 * we are going to use in the function body
 */
template<typename T>
requires EqualityComparable<T>
void fn_equality_compare(T a, T b) {
    std::cout << "Call fn_equality_compare with " << a << " and " << b << std::endl;
    if (a == b) std::cout << "  a == b" << std::endl;
    if (a != b) std::cout << "  a != b" << std::endl;
}

/**
 * Another way to require/use a concept.
 *
 * Require/Use a concept to constraint `T` be comparable by `==` and `!=`, which
 * we are going to use in the function body
 */
template<EqualityComparable T>
void fn_equality_compare2(T a, T b) {
    std::cout << "Call fn_equality_compare2 with " << a << " and " << b << std::endl;
    if (a == b) std::cout << "  a == b" << std::endl;
    if (a != b) std::cout << "  a != b" << std::endl;
}

TEST(TestConcepts, test_concepts) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;
    // following types implement the operator `==`/`!=`, hence it's ok to call with
    fn_equality_compare<double>(2.0, 2.0);
    fn_equality_compare<std::string>("A", "B");
    fn_equality_compare2<double>(2.0, 2.0);
    fn_equality_compare2<std::string>("A", "B");

    // following lines won't be compiled since std::thread has not implemented the
    //   operator `==`/`!=`, hence won't be compiled
    // fn_equality_compare<std::thread>(std::thread([](){}), std::thread([](){}));
}


/**
 * Define a concept by composing other concepts or type traits
 */
template<typename T>
concept IntEqualityComparable =
        EqualityComparable<T> &&  // composed with a concept
        std::is_integral_v<T>;    // composed with a type trait

template<typename T>
requires IntEqualityComparable<T>
void fn_int_equality_compare(T a, T b) {
    std::cout << "Call fn_int_equality_compare" << std::endl;
    if (a == b) std::cout << "  a == b" << std::endl;
    if (a != b) std::cout << "  a != b" << std::endl;
}

/**
 * Test concept by composing other concepts or type traits
 */
TEST(TestConcepts, test_composed_concepts) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;
    // int is integral and has operator `==`/`!=`, hence it's ok to call with
    fn_int_equality_compare<int>(2, 2);

    // following line won't be compiled since double is not integral
    // fn_int_equality_compare<double>(2, 2);
}