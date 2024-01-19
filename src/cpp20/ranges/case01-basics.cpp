#include <iostream>
#include <ranges>
#include <vector>

#include <gtest/gtest.h>

TEST(TestRanges, test_ranges) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto const ints = {0, 1, 2, 3, 4, 5};
    auto even = [](int i) { return 0 == i % 2; };
    auto square = [](int i) { return i * i; };

    // the traditional "functional" syntax of composing the ranges/views
    auto even_squares = std::vector<int>();
    std::cout << "squares of evens of [0, 5]:";
    for (auto const val: std::views::transform(std::views::filter(ints, even), square)) {
        std::cout << ' ' << val;
        even_squares.push_back(val);
    }
    std::cout << std::endl;

    // the "pipe" syntax of composing the ranges/views
    auto other_even_squares = std::vector<int>();
    for (auto const val: ints | std::views::filter(even) | std::views::transform(square)) {
        other_even_squares.push_back(val);
    }
    ASSERT_EQ(even_squares, other_even_squares);

}
