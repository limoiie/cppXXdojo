#include <sstream>
#include <ranges>

#include <gtest/gtest.h>

#include "utils.h"

/**
 * Demonstrate how to create ranges via factory functions.
 */
TEST(TestRangesCreation, test_factory) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    // 1/4 create an empty range
    std::ranges::empty_view<int> empty_range;
    ASSERT_TRUE(empty_range.empty());
    ASSERT_EQ(empty_range.size(), 0);

    print_range(empty_range);

    // output:

    // 2/4 create a single element range
    std::ranges::single_view<int> single_range(10);
    ASSERT_FALSE(single_range.empty());
    ASSERT_EQ(single_range.size(), 1);

    print_range(single_range);

    // output: 10

    // 3/4 create a range by repeatedly incrementing a value
    std::ranges::iota_view<int, int> iota_range(0, 10);
    ASSERT_FALSE(iota_range.empty());
    ASSERT_EQ(iota_range.size(), 10);

    print_range(iota_range);

    // output: 0 1 2 3 4 5 6 7 8 9

    // 4/4 create a range from istream by successively applying operator>> on it
    std::istringstream iss("hello world 2024");
    std::ranges::istream_view<std::string> istream_range(iss);
//    ASSERT_FALSE(istream_range.empty());  // no matching function for call to empty
//    ASSERT_EQ(istream_range.size(), 1);  // no matching function for call to size

    print_str_range(istream_range);

    // output: /hello/ /world/ /2024/

}

/**
 * Demonstrate how to create ranges from existing containers via views.
 */
TEST(TestRangesCreation, test_views) { // NOLINT(cert-err58-cpp)
    std::cout << "Testing " << __PRETTY_FUNCTION__ << " ..." << std::endl;

    auto v = std::vector<int>{1, 2, 3, 4, 5};

    // 1/2 create a range from a container
    auto sub_range_container = std::ranges::subrange(v);
    ASSERT_FALSE(sub_range_container.empty());
    ASSERT_EQ(sub_range_container.size(), 5);

    print_range(sub_range_container);

    // output: 1 2 3 4 5

    // 2/2 create a range from a pair of iterators
    auto sub_range = std::ranges::subrange(v.begin(), v.end());
    ASSERT_FALSE(sub_range.empty());
    ASSERT_EQ(sub_range.size(), 5);

    print_range(sub_range);

    // output: 1 2 3 4 5

}
