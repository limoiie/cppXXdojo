#include <iostream>
#include <ranges>
#include <vector>

#include <gtest/gtest.h>

/**
 * The ranges library is an extension and generalization of the algorithms and iterator libraries
 * that makes them more powerful by making them composable and less error-prone.
 *
 * The library creates and manipulates range views, lightweight objects
 * that indirectly represent iterable sequences (ranges).
 * Ranges are an abstraction on top of:
 * - [begin, end) - iterator pairs, e.g. range returned by implicit conversion from containers
 * - begin + [0, size) - counted sequences, e.g. range returned by std::views::counted
 * - [begin, predicated) - conditionally-terminated sequences, e.g. range returned by std::views::take_while
 * - [begin, ...) - unbounded sequences, e.g. range returned by std::views::iota
 */


/**
 * Demonstrate two basic ways of composing ranges/views.
 */
TEST(TestRanges, test_ranges) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto const ints = {0, 1, 2, 3, 4, 5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    using std::views::filter;
    using std::views::transform;

    // 1. the traditional "functional" syntax of composing the ranges/views
    for (auto const val: transform(filter(ints, even), square)) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    // output: 0 4 16

    // 2. the "pipe" syntax of composing the ranges/views
    for (auto const val: ints | filter(even) | transform(square)) {
        std::cout << val << ' ';
    }
    std::cout << std::endl;

    // output: 0 4 16

}

/**
 * Demonstrate the use of range access.
 *
 * The ranges library provides a set of functions that can be used to access
 * the underlying data of a range, a container, or an array.
 */
TEST(TestRanges, test_range_access) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // ranges access arrays
    int array[]{0, 1, 2, 3, 4, 5};
    for (auto ai = std::ranges::begin(array); ai != std::ranges::end(array); ++ai) {
        std::cout << *ai << ' ';
    }
    std::cout << std::endl;

    // output: 0 1 2 3 4 5

    ASSERT_FALSE(std::ranges::empty(array));
    ASSERT_EQ(std::ranges::size(array), 6);
    ASSERT_EQ(std::ranges::data(array), array);

    // ranges access std containers
    auto vector = std::vector<int>{0, 1, 2, 3, 4, 5};
    for (auto vi = std::ranges::cbegin(vector); vi != std::ranges::cend(vector); ++vi) {
        std::cout << *vi << ' ';
    }
    std::cout << std::endl;

    // output: 0 1 2 3 4 5

    ASSERT_FALSE(std::ranges::empty(vector));
    ASSERT_EQ(std::ranges::size(vector), 6);
    ASSERT_EQ(std::ranges::data(vector), vector.data());

    // ranges access ranges
    auto range = std::views::iota(0, 6);
    for (auto ri = std::ranges::rbegin(range); ri != std::ranges::rend(range); ++ri) {
        std::cout << *ri << ' ';
    }
    std::cout << std::endl;

    // output: 5 4 3 2 1 0

    ASSERT_FALSE(std::ranges::empty(range));
    ASSERT_EQ(std::ranges::size(range), 6);
    // error: this range is not contiguous
    //ASSERT_EQ(std::ranges::data(range), range.data());

}
