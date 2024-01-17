#include <iostream>
#include <vector>
#include <thread>

#include <gtest/gtest.h>

/**
 * Class templates, function templates,
 * and non-template functions (typically members of class templates)
 * may be associated with a constraint,
 * which specifies the requirements on template arguments,
 * which can be used
 * to select the most appropriate function overloads and template specializations.
 *
 * Constraints may also be used
 * to limit automatic type deduction in variable declarations and function return types
 * to only the types that satisfy specified requirements.
 *
 * Named sets of such requirements are called concepts.
 * Each concept is a predicate, evaluated at compile time,
 * and becomes a part of the interface of a template
 * where it is used as a constraint.
 *
 * reference from https://en.cppreference.com/w/cpp/experimental/constraints
 */

using namespace std::literals;

/**
 * First way to define a concept.
 *
 * Define a concept that requires:
 * 1. `T` to be comparable using `==` and `!=`, and
 * 2. the result type being bool.
 */
template<typename T>
concept EqComparable = requires(T a, T b) {
    // The 'requires' clause contains one or more constraints separated by commas.
    // Each constraint is satisfied by requiring the expression to be valid,
    // without needing to be true.

    // There are two ways to specify the constraints:
    // 1. Constraint the expression to be valid.
    //    This constraint is satisfied if the expression is valid, without needing to be true.
    a == b;
    a != b;
    // 2. Constraint the expression to be valid, and the result type meets a concept.
    //    This constraint is satisfied if the expression enclosed in '{' and '}' is valid
    //    and the expression's type must meet the concept specified after '->'.
    //    The concept should be partially bounded with except one parameter type not specified.
    { a == b } -> std::same_as<bool>;
    { a != b } -> std::same_as<bool>;
};

/**
 * Second way to define a concept.
 *
 * Define a concept by composing other concepts or type traits
 */
template<typename T>
concept IntEqComparable =
    // composed with a concept:
    EqComparable<T> &&
    // composed with a constexpr evaluating to true,
    //   such as a type trait;
    std::is_integral_v<T> &&
    //   or as a function call
    sizeof(T) > 1;

/**
 * First way to require/use a concept.
 *
 * Require/Use a concept to constraint `T` be comparable by `==` and `!=`, which
 * we are going to use in the function body
 */
template<IntEqComparable T>
void fn_int_equality_compare(T a, T b) {
    if (a == b) std::cout << "  a == b" << std::endl;
    if (a != b) std::cout << "  a != b" << std::endl;
}

/**
 * Second way to require/use a concept.
 *
 * Require/Use a concept to constraint `T` be comparable by `==` and `!=` which
 * we are going to use in the function body
 */
template<typename T>
requires EqComparable<T> && (sizeof(T) > 1)
void fn_equality_compare(T a, T b) {
    if (a == b) std::cout << "  a == b" << std::endl;
    if (a != b) std::cout << "  a != b" << std::endl;
}

TEST(TestConcepts, test_concepts_value) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // the evaluation of a concept returns a boolean value
    EXPECT_TRUE(EqComparable<int>);
    EXPECT_FALSE(IntEqComparable<double>);

    // the evaluation of a concept can be used as a constant expression
    constexpr auto concept_v = EqComparable<int>;
    EXPECT_TRUE(concept_v);
}

TEST(TestConcepts, test_concepts_on_functions) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // following types implement the operator `==`/`!=`, hence it's ok to call with
    fn_equality_compare<double>(2.0, 2.0);
    fn_equality_compare<std::string>("A", "B");

    // error:
    // following lines won't be compiled since std::thread has not implemented the
    //   operator `==`/`!=`, hence won't be compiled
    // fn_equality_compare<std::thread>(std::thread([](){}), std::thread([](){}));

    // int is integral and has operator `==`/`!=`, hence it's ok to call with
    fn_int_equality_compare<int>(2, 2);

    // error:
    // following line won't be compiled since double is not integral
    // fn_int_equality_compare<double>(2, 2);
}
